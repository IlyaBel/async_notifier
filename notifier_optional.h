#ifndef NOTIFIER_OPTIONAL_H
#define NOTIFIER_OPTIONAL_H

#include <optional>

template <class MessageT>
class NotifierOptional{
private:
    std::optional<MessageT> O_;

public:

    using value_type = MessageT;

    bool is_empty() const{
        return !O_.has_value();
    }

    void put_element(const MessageT& value){
        *O_ = value;
    }

    void remove_element(){
        O_.reset();
    }

    template <class Notify>
    void process_element(const Notify& notifier) const{
        notifier(*O_);
    }
};

#endif // NOTIFIER_OPTIONAL_H
