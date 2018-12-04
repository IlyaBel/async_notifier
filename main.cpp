#include "async_notifier.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

#include "queue_policy.h"

template <class ContainerT, class F>
void task(AsyncNotifier<ContainerT, F>& an){

    using namespace std::chrono_literals;

    std::srand(std::time(nullptr));
    ContainerT local_buffer;

    auto strings = std::rand()%10+1;
    for (auto i = 0; i < strings; ++i){
        typename ContainerPolicy<ContainerT>::value_type tmp_s;
        auto chars = std::rand()%10+1;
        for (auto ch = 0; ch < chars; ++ch)
            tmp_s.push_back(std::rand()%26+97);
        ContainerPolicy<ContainerT>::put_value(local_buffer, tmp_s);
        an.request(local_buffer);
    }

    while (!ContainerPolicy<ContainerT>::is_empty(local_buffer)){
        an.request(local_buffer);
        std::this_thread::sleep_for(0.1s);
    }
}

int main()
{
    auto f = [](const std::string& s){ std::cout << s << std::endl;};
    AsyncNotifier<std::queue<std::string>, decltype(f)> an(f);
    std::vector<std::thread> ths;

    constexpr size_t threads_number = 10;

    for (size_t i = 0; i < threads_number; i++)
        ths.push_back(std::thread([&an]{task(an);}));

    for (auto& th : ths)
        th.join();

    return 0;
}
