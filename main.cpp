#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

#include "async_notifier.h"
#include "notifier_queue.h"

//For queue and optional notifier

template <class Notify>
void task(AsyncNotifier<NotifierQueue<std::string>, Notify>& async_notifier){

    std::srand(std::time(nullptr));

    auto strings = std::rand()%10;
    for (auto i = 0; i < strings; ++i){
        std::string tmp_s;
        auto chars = std::rand()%10+1;
        for (auto ch = 0; ch < chars; ++ch)
            tmp_s.push_back(std::rand()%26+97);
        async_notifier.notify(tmp_s);
    }
}

//For instantaneous notifier

//template <class Notify>
//void task(AsyncNotifier<NotifierInst<std::string>, Notify>& async_notifier){

//    std::srand(std::time(nullptr));

//    auto notifies = std::rand()%10;
//    for (auto i = 0; i < notifies; ++i){
//        async_notifier.notify();
//    }
//}

int main()
{
    //For queue and optional notifier

    auto notifier = [](const std::string& s){
        std::cout << s << std::endl;
    };

    //For instantaneous notifier

//    auto notifier = [](){
//        std::cout << "Notified!" << std::endl;
//    };

    AsyncNotifier<NotifierQueue<std::string>, decltype(notifier)> q(notifier);

    std::vector<std::thread> threads;
    for (size_t i = 0; i < 100; ++i)
        threads.push_back(std::thread([&q]{task(q);}));

    for (auto& th : threads)
        th.join();

    std::cout << "----All!----" << std::endl;


    return 0;
}
