#ifndef QUEUE_POLICY_H
#define QUEUE_POLICY_H

#include "container_policy.h"
#include <queue>

template <class T>
class ContainerPolicy<std::queue<T>>{
public:
    using value_type = T;

    static bool is_empty(const std::queue<T>& Q){
        return Q.empty();
    }

    static void put_value(std::queue<T>& Q, const T& value){
        Q.push(value);
    }

    template <class F>
    static void process(std::queue<T>& Q, const F& f){
        while (!Q.empty()) {
            f(Q.front());
            Q.pop();
        }
    }
};

#endif // QUEUE_POLICY_H
