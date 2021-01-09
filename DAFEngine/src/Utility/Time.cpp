#include "Time.h"



namespace DAF
{

	size_t     Time::FPS;
	double     Time::DeltaTime;

	void Time::Hourglass::Start() {
		m_start = std::chrono::high_resolution_clock::now();
		++m_increment;
		if (m_cycle > m_tickInterval)
		{
			m_tick = m_increment;
			m_increment = 0;
			m_cycle = 0.0;
		}
	}

	void Time::Hourglass::End() {
		m_end = std::chrono::high_resolution_clock::now();
		m_dt = std::chrono::duration<double, std::ratio<1, 1>>(m_end - m_start).count();
		m_cycle += m_dt;
	}

	double Time::Hourglass::GetDelta() const { return m_dt; }
	size_t Time::Hourglass::GetTick() const { return m_tick; }

	void Time::Hourglass::ThrowElapsed(float over) const
	{
		if (over == 0.0f) over = 1.0f;
		Logger::ThrowBox("Elapsed: " + std::to_string(this->GetDelta() / over)
		);
	}

}