#include "Timer.h"

using namespace std::chrono;

const Timer& timer  = Timer::Instance();

Timer::Timer()
{
	Reset();
}

void Timer::Reset()
{
	t0 = high_resolution_clock::now();
	t1 = t0;

	m_elapsedTime = 0.0;
	m_totalTime = 0.0;
}

double Timer::GetFPS()
{
	static double fps = 0.0;
	static int numFrames = 0;
	static double totalTime = 0.0;

	totalTime += ElapsedSeconds();
	numFrames++;
	if (totalTime > 1.0)
	{
		fps = numFrames / totalTime;
		numFrames = 0;
		totalTime = 0.0;
	}

	return fps;
}

Timer& Timer::Instance()
{
	static Timer t;
	return t;
}

void Timer::Tick()
{
	t1 = high_resolution_clock::now();
	auto delta = t1 - t0;
	t0 = t1;

	m_elapsedTime = delta.count();
	m_totalTime += m_elapsedTime;
}


double Timer::ElapsedMilliSeconds() const
{
	return m_elapsedTime * 1e-6;
}
double Timer::ElapsedSeconds() const
{
	return m_elapsedTime * 1e-9;
}

double Timer::TotalTimeMilliSeconds() const
{
	return m_totalTime * 1e-6;
}
double Timer::TotalTimeSeconds() const
{
	return m_totalTime * 1e-9;
}