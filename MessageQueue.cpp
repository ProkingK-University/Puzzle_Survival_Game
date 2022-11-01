#include "MessageQueue.h"

MessageQueue::MessageQueue(int timeout) : timeout(timeout)
{
    current = timeout;

    head = NULL;
    tail = NULL;
}


void MessageQueue::addMessage(Message* m)
{
    if (m)
    {
        if (!head)
        {
            head = m;
            tail = m;
        }
        else
        {
            tail->next = m;
            tail = m;
        }
    }
}

std::string MessageQueue::print()
{
    std::string s = "";

    if (head)
    {
        if (current == 0)
        {
            Message* nodePtr = NULL;

            nodePtr = head->next;
            delete head;
            head = nodePtr;

            current = timeout;
        }

        Message* nodePtr = head;

        while (nodePtr)
        {
            s += nodePtr->getText() + '\n';

            nodePtr = nodePtr->next; 
        }

        current--;
    }
    
    return s;
}

MessageQueue::~MessageQueue()
{
    if (head)
    {
        Message* nodePtr = head;

        while (nodePtr)
        {
            head = head->next;
            delete nodePtr;
            nodePtr = head;
        }

        head = NULL;
        tail = NULL;
    }
}