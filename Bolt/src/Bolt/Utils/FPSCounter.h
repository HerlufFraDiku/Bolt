#pragma once
#include "Bolt/Core/Timestep.h"

namespace Bolt {
	class FPSCounter {
	public:
		FPSCounter(float averageOverSecs = 1.0f) : m_SecsToCount(averageOverSecs) {}
		~FPSCounter() = default;

		float FPS() { return m_FPS; }
		float FrameTime() { return m_AvgFrameTime * 1000.0f; }

		void FPSCounter::OnUpdate(Timestep dt) {
			BL_PROFILE_FUNCTION();

			m_Count += 1;
			m_Frametime += dt.GetSeconds();

			if (m_Frametime >= m_SecsToCount) {
				m_AvgFrameTime = m_Frametime / (float)m_Count;
				m_FPS = 1.0f / m_AvgFrameTime;
				m_Count = 0;
				m_Frametime = 0;
			}
		}

	private:
		float m_FPS = 0.0f, m_Frametime = 0.0f, m_SecsToCount = 1.0f, m_AvgFrameTime = 0.0f;
		int m_Count = 0;
	};

}

