/**
 * @file ringbuffer.h
 * @author kirk liang (kirk.liang00@gmail.com)
 * @brief simple ringbuffer which store arbitrary data, modyfy by kfifo.h in
 * linux kernel
 * 1 frame of data = 4 bytes(size of data) + original data
 * @version 0.1
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__

#include <sys/types.h>
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include "spdlog/spdlog.h"

struct ringbuffer
{
    unsigned int in;
    unsigned int out;
    unsigned int mask;
    // unsigned int esize;
    void *data;
};

static inline __attribute__((const)) uint32_t roundup_pow_of_two(uint32_t x)
{
    return (1 << (31 - __builtin_clz(x - 1)));
}

static inline __attribute__((const)) uint32_t rounddown_pow_of_two(uint32_t x)
{
    return ((x) == 0 ? 0
                     : 1UL << (sizeof(uint32_t) * 8 - __builtin_clzl(x) - 1));
}

#define MIN(a, b) ((a) < (b) ? (a) : (b))

static inline __attribute__((const)) bool is_power_of_2(uint32_t n)
{
    return (n != 0 && ((n & (n - 1)) == 0));
}

/*
 * internal helper to calculate the unused elements in a fifo
 */
static inline __attribute__((const)) unsigned int ringbuffer_unused(
    struct ringbuffer *fifo)
{
    return (fifo->mask + 1) - (fifo->in - fifo->out);
}

int ringbuffer_alloc(struct ringbuffer *rb, unsigned int size)
{
    /*
     * round up to the next power of 2, since our 'let the indices
     * wrap' technique works only in this case.
     */
    if (size & (size - 1))
    {
        if ((size > 0x80000000))
            return -EINVAL;

        size = roundup_pow_of_two(size);
        spdlog::info("{}:{} size = {}", __FILE__, __LINE__, size);
    }

    rb->in = 0;
    rb->out = 0;

    if (size < 2)
    {
        rb->data = NULL;
        rb->mask = 0;
        return -EINVAL;
    }

    // TODO: promise the allocated object address is aligned to at least
    // ARCH_KMALLOC_MINALIGN
    rb->data = malloc(size);

    if (!rb->data)
    {
        rb->mask = 0;
        return -ENOMEM;
    }

    rb->mask = size - 1;
    return 0;
}

void ringbuffer_free(struct ringbuffer *rb)
{
    free(rb->data);
    rb->in = 0;
    rb->out = 0;
    rb->data = NULL;
    rb->mask = 0;
}

#if 0
int ringbuffer_init(struct ringbuffer *rb, void *buffer, unsigned int size)
{
    if (!is_power_of_2(size))
        size = rounddown_pow_of_two(size);

    rb->in = 0;
    rb->out = 0;
    rb->data = buffer;

    if (size < 2)
    {
        rb->mask = 0;
        return -EINVAL;
    }
    rb->mask = size - 1;

    return 0;
}
#endif

int ringbuffer_in(struct ringbuffer *rb, const void *buf, unsigned int len)
{
    // no enough space
    if (ringbuffer_unused(rb) < len + 4)
        return -EINVAL;

    void *buffer = malloc(len + 4);
    if (!buffer)
        return -ENOMEM;

    memcpy((char *)buffer, &len, 4);
    memcpy((char *)buffer + 4, buf, len);
    len += 4;
    spdlog::info("{}:{} buf: {}, len: {}", __FILE__, __LINE__,
                 (char *)buffer + 4, len);

    /* first put the data starting from fifo->in to buffer end */
    unsigned int l = MIN(len, rb->mask + 1 - (rb->in & rb->mask));

    // lock or smp_wmb();

    memcpy((char *)rb->data + (rb->in & rb->mask), (char *)buffer, l);

    /* then put the rest (if any) at the beginning of the buffer */
    memcpy((char *)rb->data, (char *)buffer + l, len - l);

    // lock or smp_wmb();
    free(buffer);

    // When unsigned int overflows, it will be set to 0.
    rb->in += len;
    return len;
}

unsigned int ringbuffer_out(struct ringbuffer *rb, unsigned char *buf)
{
    if (rb->in == rb->out)
        return -EINVAL;

    unsigned int len = 4, high = 0, low = 0;
    unsigned int l = MIN(len, rb->mask + 1 - (rb->out & rb->mask));

    // lock or smp_rmb();

    // get data len
    memcpy(&high, (char *)rb->data + (rb->out & rb->mask), l);
    memcpy(&low, rb->data, len - l);

    rb->out += 4;
    len = (high << (len - l)) | low;

    // get data
    l = MIN(len, rb->mask + 1 - (rb->out & rb->mask));

    memcpy(buf, (char *)rb->data + (rb->out & rb->mask), l);
    memcpy(buf, (char *)rb->data, len - l);

    // lock or smp_mb();

    rb->out += len;

    return len;
}

#endif /* __RINGBUFFER_H__ */