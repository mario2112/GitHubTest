#pragma once

template< class DataType >
class CTimer
{
public:

	using TimerSystemClock = std::chrono::system_clock;
	using TimerDuration = std::chrono::duration< double >;
	using TimerTimePoint = std::chrono::system_clock::time_point;
	using TimerNanoSeconds = std::chrono::duration< DataType, std::nano >;
	using TimerMicroSeconds = std::chrono::duration< DataType, std::micro >;
	using TimerMilliSeconds = std::chrono::duration< DataType, std::milli >;
	using TimerSeconds = std::chrono::duration< DataType >;
	using TimerMinutes = std::chrono::duration< DataType, std::ratio< 60 > >;
	using TimerHours = std::chrono::duration< DataType, std::ratio< 60 * 60 > >;
	using TimerDays = std::chrono::duration< DataType, std::ratio< 60 * 60 * 24 > >;

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
	TimerDuration m_tRunTime{ TimerDuration::zero() };
};

typedef std::shared_ptr< CTimer< float > > TimerHandle;
typedef std::shared_ptr< CTimer< float > > FloatTimerHandle;
typedef std::shared_ptr< CTimer< double > > DoubleTimerHandle;
typedef std::shared_ptr< CTimer< int > > IntTimerHandle;
typedef std::shared_ptr< CTimer< long > > LongTimerHandle;
typedef std::shared_ptr< CTimer< long long > > LonglongTimerHandle;