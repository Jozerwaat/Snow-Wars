#pragma once
#include <chrono>

class Timer
{
public:
	Timer();

	/// <summary>
	/// Get the global timer instance.
	/// </summary>
	/// <returns></returns>
	static Timer& Instance();

	/// <summary>
	/// Tick once per frame (by game class).
	/// </summary>
	void Tick();

	/// <summary>
	/// Reset timer.
	/// </summary>
	void Reset();

	int GetFPS();

	double ElapsedMilliSeconds() const;
	double ElapsedSeconds() const;

	double TotalTimeMilliSeconds() const;
	double TotalTimeSeconds() const;

private:
	std::chrono::high_resolution_clock::time_point t0, t1;
	double m_elapsedTime;
	double m_totalTime;

};
