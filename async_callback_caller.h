#ifndef ASYNC_CALLBACK_CALLER_H
#define ASYNC_CALLBACK_CALLER_H

#include <future>
#include <mutex>

class AsyncCallbackCaller {
private:
    std::future<void> executor_;

public:
    AsyncCallbackCaller();

    bool is_ready();

    template<class F>
    void operator () (const F& f){
        executor_ = std::async(std::launch::async, f);
    }

    ~AsyncCallbackCaller();
};

#endif // ASYNC_CALLBACK_CALLER_H
