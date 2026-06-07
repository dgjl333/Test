#pragma once
#include <atomic>

template<typename E, int N>
class TrackedEnum
{
private:
	inline static std::atomic<int> mCounts[N] = {};

	E mEnum;

public:
    constexpr static int enumCount = N;

    TrackedEnum(E initial = E{}) : mEnum(initial)
    {
        mCounts[static_cast<int>(initial)]++;
    }

    ~TrackedEnum()
    {
        mCounts[static_cast<int>(mEnum)]--;
    }

    TrackedEnum(const TrackedEnum&) = delete;             
    TrackedEnum(TrackedEnum&&) = delete;                  
    TrackedEnum& operator=(const TrackedEnum&) = delete;  
    TrackedEnum& operator=(TrackedEnum&&) = delete;

    TrackedEnum& operator=(E newValue)
    {
        mCounts[static_cast<int>(mEnum)]--;   
        mEnum = newValue;
        mCounts[static_cast<int>(mEnum)]++;  
        return *this;
    }

    operator E() const { return mEnum; }

    static int getCounts(E e) { return mCounts[static_cast<int>(e)].load(std::memory_order_relaxed); }
};