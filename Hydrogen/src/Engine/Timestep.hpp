#pragma once

namespace Hydrogen
{
	class Timestep
	{
	public:
		Timestep(float time_seconds = 0.0f)
			: m_Time(time_seconds)
		{}

		operator float() const { return m_Time; }

		float GetSeconds() { return m_Time; }
		float GetMilliseconds() { return (m_Time * 1000.0f); }

	private:
		float m_Time;
	};
	
}