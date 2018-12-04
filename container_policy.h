#ifndef CONTAINER_POLICY_H
#define CONTAINER_POLICY_H

template <class ContainerT>
class ContainerPolicy{
public:
    using value_type = typename ContainerT::value_type;

    static bool is_empty(const ContainerT& cont);

    static void put_value(ContainerT& cont, const value_type& value);

    template <class F>
    static void process(ContainerT& cont, const F& f);
};

#endif // CONTAINER_POLICY_H
