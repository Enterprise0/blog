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
std::vector<int> client_fds(MAX_EVENTS, -1);

void addClient(int client_fd)
{
    auto it = std::find(client_fds.begin(), client_fds.end(), -1);
    if (it != client_fds.end()) {
        *it = client_fd;
    }
}

void removeClient(int client_fd)
{
    auto it = std::find_if(client_fds.begin(), client_fds.end(), [client_fd](int x) { return x == client_fd; });
    if (it != client_fds.end()) {
        *it = -1;
    }
}

void handleEvents(int epoll_fd, int server_fd, int thread_id, std::vector<int>& client_fds)
{
    struct epoll_event events[MAX_EVENTS];
    int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);

    for (int i = 0; i < num_events; ++i)
    {
        if (events[i].data.fd != server_fd &&
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
                    removeClient(events[i].data.fd);
                }
                continue;
            }

            if (bytes_read == 0)
            {
                // Client disconnected
                close(events[i].data.fd);
                {
                    std::lock_guard<std::mutex> lock(mtx);
                    removeClient(events[i].data.fd);
                }
                continue;
            }

            // Process received data
            for (int i = 0; i < 1000000; ++i)
            {

            }
            spdlog::debug("thread {} Received: {}", thread_id, std::string(buffer));
        }
    }
}

void worker(int epoll_fd, int server_fd, int thread_id, std::vector<int>& client_fds)
{
    while (true)
    {
        handleEvents(epoll_fd, server_fd, thread_id, client_fds);
    }
}

int main()
{
    spdlog::set_level(spdlog::level::info);
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

    std::vector<std::thread> workers;

    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        workers.emplace_back(worker, epoll_fd, server_fd, i, std::ref(client_fds));
    }

    for (auto& worker : workers)
    {
        worker.detach();
    }

    //std::thread([](){
    //    while(true)
    //    {
    //        int count = std::count_if(client_fds.begin(), client_fds.end(), [](int x) { return x != -1; });
    //        if (count != 0)
    //            spdlog::info("client_lens: {}", count);
    //    }
    //}).detach();

    int client_sum = 0;
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
                    addClient(client_fd);
                }
                ++client_sum;
                spdlog::debug("Accepted new connection, sum: {}", client_sum);
            }
        }
    }

    return 0;
}
