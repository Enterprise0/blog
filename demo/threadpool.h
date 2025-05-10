#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

class ThreadPool {
public:
    ThreadPool(size_t n);

    ~ThreadPool();

    template <typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<decltype(f(args...))>;

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

private:
    bool stop_;
    std::mutex mutex_;
    std::condition_variable cv_;

    std::vector<std::thread> worker_;
    std::queue<std::function<void()>> taskQueue_;
};

ThreadPool::ThreadPool(size_t n)
    : stop_(false) {
    for (size_t i = 0; i < n; ++i) {
        worker_.emplace_back(std::thread([this] {
            for (;;) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lk(mutex_);
                    cv_.wait(lk, [this] { return stop_ || !taskQueue_.empty(); });
                    if (stop_ && taskQueue_.empty()) {
                        return;
                    }
                    task = std::move(taskQueue_.front());
                    taskQueue_.pop();
                }
                task();
            }
        }));
    }
}

template <typename F, typename... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
    using return_type = decltype(f(args...));

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    {
        std::lock_guard<std::mutex> lk(mutex_);
        taskQueue_.emplace([task]() { (*task)(); });
    }
    cv_.notify_one();

    return task->get_future();
}

ThreadPool::~ThreadPool() {
    {
        std::lock_guard<std::mutex> lk(mutex_);
        stop_ = true;
    }
    cv_.notify_all();
    for (auto& thread : worker_) {
        thread.join();
    }
}

/*
int main(int argc, char** argv) {
    ThreadPool pool(10);

    std::vector<std::future<int>> res;
    for (int i = 0; i < 100; ++i) {
        res.emplace_back(pool.enqueue([i] { return i; }));
    }

    for_each(res.begin(), res.end(), [](std::future<int> &res) { std::cout << res.get() << " "; });
}
*/
#endif /* THREAD_POOL_H */