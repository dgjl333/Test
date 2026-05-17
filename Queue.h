#pragma once
#include <vector>

template<typename T>
class Queue
{
private:

    std::vector<T> data;
    int mTail = 0;
    int mHead = 0;
    int mCount = 0;

    void resize() 
    {
        std::vector<T> newData;
        newData.resize(data.size() * 2);
        for (int i = 0; i < mCount; i++)
        {
            newData[i] = data[(mTail + i) % data.size()];
        }
        data = std::move(newData);
        mTail = 0;
        mHead = mCount;
    }

public:

    Queue()
    {
        data.resize(4);
    }

    void push(T value)
    {
        if (mCount == (int)data.size())
        {
            resize();
        }

        data[mHead] = value;
        mHead = (mHead + 1) % data.size();
        mCount++;
    }

    void pop()
    {
        if (mCount == 0) return;
        mTail = (mTail + 1) % data.size();
        mCount--;
    }

    void clear()
    {
        mTail = 0;
        mHead = 0;
        mCount = 0;
	}

    T front() const
    {
        return data[mTail];
    }

    int size() const
    {
        return mCount;
	}
};