# Changelog

- v1.0.0 add reactor demo: single reactor multi worker threads
- v1.0.1 用数组替换容器，空间换时间

# Tips
- 有没有可能client_fds中存在重复的client socket fd
  修改close位置可以解决
- 高并发场景下，sock可能刚关闭就被打开，所以没有用`EPOLL_CTL_DEL`。
  哈希可以改成条件变量唤醒+任务队列，可以关闭TIME_WAIT，另外这两个demo写的依托。
