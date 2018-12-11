#ifndef NOTIFIER_QUEUE_H
#define NOTIFIER_QUEUE_H

#include <queue>

template <class MessageT>
class NotifierQueue{
private:
    std::queue<MessageT> Q_;

public:

    using value_type = MessageT;

    bool is_empty() const{
        return Q_.empty();
    }

    void put_element(const MessageT& value){
        Q_.push(value);
    }

    void remove_element(){
        Q_.pop();
    }

    template <class Notify>
    void process_element(const Notify& notifier) const{
        notifier(Q_.front());
    }
};

#endif // NOTIFIER_QUEUE_H
