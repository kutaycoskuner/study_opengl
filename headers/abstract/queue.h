#pragma once
// library
// ---------------------------------------------------------------------------------------
#include <vector>
#include <iostream>

// abstract
// ---------------------------------------------------------------------------------------
template<class T> // meta programming compiler kodu senin adina generate ediyor
class Queue
{
public:
	// default constructor
	Queue() = default;
	// copy constructor
	// parameter contructor

	// functions
	void add(const T& item)		{
		data.push_back(item);
	};

	void remove()	{
		if (!data.empty()) {
			data.erase(data.begin());
		}
	};

	T  peek() const		{
		if (data.empty()) {
			std::cout << "ERROR: QUEUE IS EMPTY RETURNED DEFAULT VALUE '-1'";
			return T();
		}
		
		return data[0];
	};

	size_t size() const {
		return data.size();
	}

	bool is_empty() const	{
		return data.size() == 0;
	};

private:
	std::vector<T> data;
};