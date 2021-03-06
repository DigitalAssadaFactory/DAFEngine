#pragma once
#include <chrono>
#include "Logger.h"



namespace DAF
{

	struct Time {
		static size_t   FPS;
		static double     DeltaTime;

		struct Hourglass {
			Hourglass() : m_cycle(0.0), m_tickInterval(1.0) {}
			Hourglass(const double& tickInterval) : m_cycle(0.0), m_tickInterval(tickInterval) {}
			void Start();
			void End();
			double GetDelta() const;
			size_t GetTick() const;
			void ThrowElapsed(float over = 1.0f) const;
		private:
			std::chrono::time_point<std::chrono::steady_clock>   m_start;
			std::chrono::time_point<std::chrono::steady_clock>   m_end;
			double                                               m_cycle;
			size_t                                             m_tick;
			double                                               m_dt;
			size_t                                             m_increment;
			const double                                         m_tickInterval;
		};
	};

}