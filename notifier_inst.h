#ifndef NOTIFIER_INST_H
#define NOTIFIER_INST_H

#include <cstddef>

template <class MessageT>
class NotifierInst{
private:
    std::size_t counter_ = 0;

public:

    using value_type = MessageT;

    bool is_empty() const{
        return counter_ == 0;
    }

    void put_element(){
        ++counter_;
    }

    void remove_element(){
        --counter_;
    }

    template <class Notify>
    void process_element(const Notify& notifier) const{
        notifier();
    }
};

#endif // NOTIFIER_INST_H
