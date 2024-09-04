#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>
#include "spdlog/spdlog.h"

const int MAX_EVENTS = 100;
const int MAX_CLIENTS = 10;

std::mutex mtx; // Mutex to protect client_fds

void handleEvents(int epoll_fd, int socket_fd, int thread_id, std::vector<int>& client_fds)
{
    struct epoll_event events[MAX_EVENTS];
    int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);

    for (int i = 0; i < num_events; ++i)
    {
        if (events[i].data.fd != socket_fd &&
            events[i].data.fd % MAX_CLIENTS == thread_id)
        {
            // Read data from client socket
            char buffer[1024];
            ssize_t bytes_read = read(events[i].data.fd, buffer, sizeof(buffer));
            if (bytes_read == -1)
            {
                spdlog::error("thread {} Error reading from client socket: {}", thread_id, strerror(errno));
                close(events[i].data.fd);
                {
                    std::lock_guard<std::mutex> lock(mtx);
                    client_fds.erase(std::remove(client_fds.begin(), client_fds.end(), events[i].data.fd), client_fds.end());
                }
                continue;
            }

            if (bytes_read == 0)
            {
                // Client disconnected
                close(events[i].data.fd);
                {
                    std::lock_guard<std::mutex> lock(mtx);
                    client_fds.erase(std::remove(client_fds.begin(), client_fds.end(), events[i].data.fd), client_fds.end());
                }
                continue;
            }

            // Process received data
            spdlog::info("thread {} Received: {} client_lens: {}", thread_id, std::string(buffer), client_fds.size());
        }
    }
}

void worker(int epoll_fd, int socket_fd, int thread_id, std::vector<int>& client_fds)
{
    while (true)
    {
        handleEvents(epoll_fd, socket_fd, thread_id, client_fds);
    }
}

int main()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        spdlog::error("Error creating server socket: {}", strerror(errno));
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(6666);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        spdlog::error("Error binding server socket: {}", strerror(errno));
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, SOMAXCONN) == -1)
    {
        spdlog::error("Error listening on server socket: {}", strerror(errno));
        close(server_fd);
        return 1;
    }

    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1)
    {
        spdlog::error("Error creating epoll: {}", strerror(errno));
        close(server_fd);
        return 1;
    }

    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = server_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event) == -1)
    {
        spdlog::error("Error adding server socket to epoll: {}", strerror(errno));
        close(epoll_fd);
        close(server_fd);
        return 1;
    }

    std::vector<int> client_fds;
    std::vector<std::thread> workers;

    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        workers.emplace_back(worker, epoll_fd, server_fd, i, std::ref(client_fds));
    }

    for (auto& worker : workers)
    {
        worker.detach();
    }

    while(true)
    {
        struct epoll_event events[MAX_EVENTS];
        int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);

        for (int i = 0; i < num_events; ++i)
        {
            if (events[i].data.fd == server_fd)
            {
                // Accept new connection
                int client_fd = accept(server_fd, nullptr, nullptr);
                if (client_fd == -1)
                {
                    spdlog::error("Error accepting connection: {}", strerror(errno));
                    continue;
                }

                // Add client socket to epoll
                struct epoll_event event;
                event.events = EPOLLIN;
                event.data.fd = client_fd;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event) == -1)
                {
                    spdlog::error("Error adding client socket to epoll: {}", strerror(errno));
                    close(client_fd);
                    continue;
                }

                {
                    std::lock_guard<std::mutex> lock(mtx);
                    client_fds.push_back(client_fd);
                }
            }
        }
    }

    return 0;
}
