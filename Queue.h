#pragma once

template<typename T>
class Queue
{
private:

    struct Node
    {
        T value;
        Node* next = nullptr;
    };

    Node* mTail = nullptr;
    Node* mHead = nullptr;

    int mCount = 0;

public:

    Queue() = default;

    ~Queue()
    {
        clear();
    }

    void push(T value)
    {
        Node* newNode = new Node();
        newNode->value = value;

        if (mHead)
        {
            mHead->next = newNode;
        }
        else
        {
            mTail = newNode;
        }

        mHead = newNode;
        mCount++;
    }

    void pop()
    {
        if (mCount == 0)
        {
            return;
        }

        Node* oldTail = mTail;

        mTail = mTail->next;

        delete oldTail;

        mCount--;

        if (mCount == 0)
        {
            mHead = nullptr;
        }
    }

    void clear()
    {
        while (mTail)
        {
            Node* next = mTail->next;
            delete mTail;
            mTail = next;
        }

        mHead = nullptr;
        mCount = 0;
    }

    T front() const
    {
        return mTail->value;
    }

    int size() const
    {
        return mCount;
    }
};