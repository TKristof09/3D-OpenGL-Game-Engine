#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
	Timer();
	~Timer();
	void Start();
	void Stop();
	void Pause();
	void UnPause();
	int GetTicks();
	inline bool IsPaused() const { return paused; };
	inline bool IsStarted() const { return started; };
private:
	bool started;
	bool paused;
	int startTicks;
	int pausedTicks;
};


#endif // !TIMER_H


