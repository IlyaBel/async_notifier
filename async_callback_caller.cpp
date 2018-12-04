#include "async_callback_caller.h"

bool AsyncCallbackCaller::is_ready(){
    return executor_.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
}

AsyncCallbackCaller::AsyncCallbackCaller(){
    executor_ = std::async([]{});
    executor_.wait();
}

AsyncCallbackCaller::~AsyncCallbackCaller(){
    executor_.wait();
}
