#pragma once
#include <atomic>
#include <initializer_list>
#include <vector>

struct TrackedArrayMemory
{
public:
	static size_t getHeapMemoryUsed()  { return mHeapMemoryUsed.load(std::memory_order_relaxed); }

private:
	inline static std::atomic<size_t> mHeapMemoryUsed = 0;

	template<typename T>
	friend class TrackedArray;
};

template<typename T>
class TrackedArray
{
public:
	TrackedArray() {}
	~TrackedArray()
	{
		TrackedArrayMemory::mHeapMemoryUsed -= mData.capacity() * sizeof(T);
	}

	TrackedArray(const TrackedArray&) = delete;

	TrackedArray(TrackedArray&&) = delete;

	TrackedArray& operator = (const TrackedArray&) = delete;

	TrackedArray& operator = (TrackedArray&&) = delete;

	TrackedArray& operator = (std::initializer_list<T> list)
	{
		trackMemory([&]() { mData = list; });
		return *this;
	}

	auto begin() { return mData.begin(); }
	auto end() { return mData.end(); }
	auto begin() const { return mData.begin(); }
	auto end()   const { return mData.end(); }

	T& operator[](size_t i) { return mData[i]; }
	const T& operator[](size_t i) const { return mData[i]; }

	size_t size() const { return mData.size(); }

	bool empty() const { return mData.empty(); }

	void clear()
	{
		trackMemory([&]() { mData.clear(); });
	}

	void emplaceBack(const T& value)
	{
		trackMemory([&]() { mData.emplace_back(value); });
	}

	void destroy()
	{
		trackMemory([&]() { mData = std::vector<T>(); });
	}

private:
	std::vector<T> mData;

	void updateMemoryUsage(size_t oldCap)
	{
		size_t newCap = mData.capacity();
		if (oldCap == newCap)
		{
			return;
		}

		if (newCap > oldCap)
		{
			TrackedArrayMemory::mHeapMemoryUsed += (newCap - oldCap) * sizeof(T);
		}
		else
		{
			TrackedArrayMemory::mHeapMemoryUsed -= (oldCap - newCap) * sizeof(T);
		}
	}

	template<typename Func>
	void trackMemory(Func fn)
	{
		size_t oldCap = mData.capacity();
		fn();
		updateMemoryUsage(oldCap);
	}
};

