#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <chrono>

class Timer
{
public:
	Timer();
	~Timer() = default;

	Timer(const Timer& other) = default;
	Timer(Timer&& other) = default;
	Timer& operator=(const Timer& other) = default;
	Timer& operator=(Timer&& other) = default;

	float Mark();
	float Peek() const;

private:
	std::chrono::steady_clock::time_point last;

};


#endif // !TIMER_H_INCLUDED