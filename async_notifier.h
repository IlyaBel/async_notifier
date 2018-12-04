#ifndef ASYNC_NOTIFIER_H
#define ASYNC_NOTIFIER_H

#include "container_policy.h"
#include "async_callback_caller.h"
#include <mutex>
#include <cassert>

template <class ContainerT, class F>
class AsyncNotifier {
private:
    AsyncCallbackCaller caller_;
    std::mutex request_mutex;
    ContainerT container_;
    const F f_;

public:
    AsyncNotifier(const F& f) : f_(f) {}

    bool request(ContainerT& side_storage){
        std::lock_guard<std::mutex> lck(request_mutex);
        if (!caller_.is_ready())
            return false;
        else{
            assert(ContainerPolicy<ContainerT>::is_empty(container_));
            std::swap(container_, side_storage);
            caller_([this]{ContainerPolicy<ContainerT>::process(container_, f_);});
            return true;
        }
    }
};

#endif // ASYNC_NOTIFIER_H
