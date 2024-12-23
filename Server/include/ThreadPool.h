#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <boost/asio/io_context.hpp>
#include <vector>
#include <thread>

class ThreadPool
{
public:
    explicit ThreadPool(boost::asio::io_context& io_context);

    void stop();

private:
    void start();

    ~ThreadPool();

    uint32_t max_threads_;
    boost::asio::io_context& io_context_;
    std::vector<std::thread> thread_pool_;
};

#endif // THREADPOOL_H
