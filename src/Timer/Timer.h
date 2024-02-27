
#ifndef TIMER_H
#define TIMER_H

const int TARGET_FPS = 60;
const float TARGET_DEALTATIME = 1.5f;

class Timer
{
public:
	void Tick();
	inline float GetDealtaTime() { return m_DeltaTime; }
	inline static Timer* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Timer(); }

private:
	Timer(){}
	static Timer* s_Instance;
	float m_DeltaTime;
	
	float m_LastTime;
};

#endif