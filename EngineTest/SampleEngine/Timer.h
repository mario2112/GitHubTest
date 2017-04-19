#pragma once

class CTimer
{
public:

	using TimerSystemClock = std::chrono::system_clock;
	using TimerTimePoint = std::chrono::system_clock::time_point;
	using TimerNanoSeconds = std::chrono::duration< float, std::nano >;
	using TimerMicroSeconds = std::chrono::duration< float, std::micro >;
	using TimerMilliSeconds = std::chrono::duration< float, std::milli >;
	using TimerSeconds = std::chrono::duration< float >;
	using TimerMinutes = std::chrono::duration< float, std::ratio< 60 > >;
	using TimerHours = std::chrono::duration< float, std::ratio< 60 * 60 > >;
	using TimerDays = std::chrono::duration< float, std::ratio< 60 * 60 * 24 > >;

public:
	CTimer(){}
	CTimer( CTimer& refTimer ) = delete;
	virtual ~CTimer(){}

	virtual void execute() noexcept
	{
		TimerTimePoint tStart{ TimerSystemClock::now() };
		m_tRunTime = tStart - m_tCreateTime;
	}

	//constexpr ChronoTimePoint getRunTime() const noexcept { return m_tCreateTime; };
	constexpr TimerSeconds getRunTimeSeconds() const noexcept { return m_tRunTime; };
	template< typename T >
	const T getRuntime() const noexcept { return std::chrono::duration_cast< T >( m_tRunTime ); };

protected:

	TimerTimePoint m_tCreateTime{ TimerSystemClock::now() };
	TimerSeconds m_tRunTime{ TimerSeconds::zero() };
};