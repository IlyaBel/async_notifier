#ifndef OPTIONAL_POLICY_H
#define OPTIONAL_POLICY_H

#include "container_policy.h"
#include <optional>

template <class T>
class ContainerPolicy<std::optional<T>>{
public:
    using value_type = T;

    static bool is_empty(const std::optional<T>& O){
        return O.has_value();
    }

    static void put_value(std::optional<T>& O, const T& value){
        *O = value;
    }

    template <class F>
    static void process(std::optional<T>& O, const F& f){
        if (O.has_value()){
            f(O.value());
            O.reset();
        }
    }
};

#endif // OPTIONAL_POLICY_H
