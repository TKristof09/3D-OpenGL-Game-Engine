#ifndef TIME_H
#define TIME_H

class Time
{
public:
	static double GetTime();
	static double GetDelta();

	static void SetDelta(double value);
private:
	static double m_delta;
};

#endif // !TIME_H