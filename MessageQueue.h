#ifndef MESSAGE_Q_H
#define MESSAGE_Q_H

#include "Message.h"
#include <string>

class MessageQueue
{
private:
    int current;
    int timeout;

    Message* head;
    Message* tail;
public:
    MessageQueue(int timeout);

    std::string print();
    void addMessage(Message* m);

    ~MessageQueue();
};

#endif