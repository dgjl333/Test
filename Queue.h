#pragma once
#include <vector>

template<typename T>
class Queue
{
private:

    std::vector<T> mData;
    int mTail = 0;
    int mHead = 0;
    int mCount = 0;

    void resize() 
    {
        std::vector<T> newData;
        newData.resize(mData.size() * 2);
        for (int i = 0; i < mCount; i++)
        {
            newData[i] = mData[(mTail + i) % mData.size()];
        }
        mData = std::move(newData);
        mTail = 0;
        mHead = mCount;
    }

public:

    Queue()
    {
        mData.resize(4);
    }

    void push(T value)
    {
        if (mCount == (int)mData.size())
        {
            resize();
        }

        mData[mHead] = value;
        mHead = (mHead + 1) % mData.size();
        mCount++;
    }

    void pop()
    {
        if (mCount == 0) return;
        mTail = (mTail + 1) % mData.size();
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
        return mData[mTail];
    }

    int size() const
    {
        return mCount;
	}
};