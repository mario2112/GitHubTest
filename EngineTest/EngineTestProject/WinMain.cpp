#include "stdafx.h"
#include "AsyncInputCommand.h"
#include "Timer.h"

void SampleInput( ICommand::enKeyState KeyState )
{
	printf( "Success Callback SampleInput\n" );
}

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow )
{
	CAsyncInputCommand tt( VK_LEFT, SampleInput );

	CTimer TestTimer;

	while( 1 )
	{
		TestTimer.execute();

		printf( "Nano = %lf, Micro = %lf, Milli = %lf, Seconds = %lf, Minutes = %lf, Hours = %lf, Days = %lf\n"
			, TestTimer.getRuntime< CTimer::TimerNanoSeconds >().count()
			, TestTimer.getRuntime< CTimer::TimerMicroSeconds >().count()
			, TestTimer.getRuntime< CTimer::TimerMilliSeconds >().count()
			, TestTimer.getRuntime< CTimer::TimerSeconds >().count()
			, TestTimer.getRuntime< CTimer::TimerMinutes >().count()
			, TestTimer.getRuntime< CTimer::TimerHours >().count()
			, TestTimer.getRuntime< CTimer::TimerDays >().count()
			);
	}

	return 0;
}