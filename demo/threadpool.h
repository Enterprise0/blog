#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

class threadpool {
public:
    threadpool(size_t n);

    ~threadpool();

    template <typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<decltype(f(args...))>;

private:
    std::mutex mutex_;
    std::condition_variable cv_;
    std::vector<std::thread> worker_;
    std::queue<std::function<void()>> taskQueue;
    bool stop_;
};

threadpool::threadpool(size_t n)
    : stop_(false) {
    for (size_t i = 0; i < n; ++i) {
        worker_.emplace_back(std::thread([this] {
            for (;;) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lk(mutex_);
                    cv_.wait(lk, [this] { return stop_ || !taskQueue.empty(); });
                    if (stop_) {
                        return;
                    } else {
                        task = std::move(taskQueue.front());
                        taskQueue.pop();
                    }
                }
                task();
            }
        }));
    }
}

template <typename F, typename... Args>
auto threadpool::enqueue(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
    using return_type = typename std::future<decltype(f(args...))>;

    auto task = std::make_shared<std::packaged_task<return_type(Args...)>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    return_type res = task.get_future();
    {
        std::lock_guard<std::mutex> lk(mutex_);
        taskQueue.emplace([task]() { (*task)(); });
    }
    cv_.notify_one();

    return res;
}

threadpool::~threadpool() {
    {
        std::lock_guard<std::mutex> lk(mutex_);
        stop_ = true;
    }
    cv_.notify_all();
    for (auto& thread : worker_) {
        thread.join();
    }
}