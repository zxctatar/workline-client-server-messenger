#include "../../include/ThreadPool.h"

ThreadPool::ThreadPool(boost::asio::io_context& io_context)
    : io_context_(io_context), max_threads_(std::thread::hardware_concurrency())
{
    if(max_threads_ < 2)
    {
        max_threads_ = 2;
    }

    start();
}

void ThreadPool::start()
{
    for(int i = 0; i < max_threads_; ++i)
    {
        thread_pool_.emplace_back([this](){
            io_context_.run();
        });
    }
}

void ThreadPool::stop()
{
    io_context_.stop();

    for(auto& t : thread_pool_)
    {
        if(t.joinable())
        {
            t.join();
        }
    }
}
