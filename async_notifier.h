#ifndef ASYNC_NOTIFIER_H
#define ASYNC_NOTIFIER_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <algorithm>

template <class ContainerT, class Notify>
class AsyncNotifier{
private:
    ContainerT cont_;
    std::mutex mx_;
    const Notify notifier_;
    std::thread notification_thread;
    std::condition_variable cv_;
    std::atomic_bool stop_flag = false;

    void notification_job();

public:
    AsyncNotifier(const Notify& notifier);

    //For queue, optional, etc. notifiers
    void notify(const typename ContainerT::value_type& message);

    //For instantaneous notifier
    void notify();

    ~AsyncNotifier();
};

#endif // ASYNC_NOTIFIER_H

template<class ContainerT, class Notify>
void AsyncNotifier<ContainerT, Notify>::notification_job(){
    while(true){
        //Wait until container not empty or stop flag isn't set
        {
            std::unique_lock lck(mx_);
            cv_.wait(lck, [this]{return !cont_.is_empty() || stop_flag;});
        }

        //If stop flag is not set, thread has been awaken by !cont_.is_empty()
        //and we need to notify all the messages
        if (!stop_flag){
            ContainerT tmp_cont;
            {
                std::lock_guard lck(mx_);
                std::swap(cont_, tmp_cont);
            }
            while (!tmp_cont.is_empty()) {
                tmp_cont.process_element(notifier_);
                tmp_cont.remove_element();
            }

        }
        //If stop flag is set
        else {
            break;
        }
    }
}

template<class ContainerT, class Notify>
AsyncNotifier<ContainerT, Notify>::AsyncNotifier(const Notify &notifier) : notifier_(notifier) {
    notification_thread = std::thread([this]{notification_job();});
}

template<class ContainerT, class Notify>
void AsyncNotifier<ContainerT, Notify>::notify(const typename ContainerT::value_type &message){
    {
        std::lock_guard lck(mx_);
        cont_.put_element(message);
    }

    cv_.notify_one();
}

template<class ContainerT, class Notify>
void AsyncNotifier<ContainerT, Notify>::notify(){
    {
        std::lock_guard lck(mx_);
        cont_.put_element();
    }

    cv_.notify_one();
}

template<class ContainerT, class Notify>
AsyncNotifier<ContainerT, Notify>::~AsyncNotifier(){
    stop_flag = true;
    cv_.notify_one();
    notification_thread.join();
}
