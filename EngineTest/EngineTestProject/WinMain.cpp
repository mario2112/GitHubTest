#include "stdafx.h"
#include "AsyncInputCommand.h"
#include "CTimer.h"

void SampleInput( ICommand::enKeyState KeyState )
{
	printf( "Success Callback SampleInput\n" );
}

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow )
{
	CAsyncInputCommand tt( VK_LEFT, SampleInput );

	CTimer< long long > TestTimer;

	while( 1 )
	{
		TestTimer.execute();

		printf( "Nano = %lld, Micro = %lld, Milli = %lld, Seconds = %lld, Minutes = %lld, Hours = %lld, Days = %lld\n"
			, TestTimer.getRuntime< CTimer< long long >::TimerNanoSeconds >().count()
			, TestTimer.getRuntime< CTimer< long long >::TimerMicroSeconds >().count()
			, TestTimer.getRuntime< CTimer< long long >::TimerMilliSeconds >().count()
			, TestTimer.getRuntime< CTimer< long long >::TimerSeconds >().count()
			, TestTimer.getRuntime< CTimer< long long >::TimerMinutes >().count()
			, TestTimer.getRuntime< CTimer< long long >::TimerHours >().count()
			, TestTimer.getRuntime< CTimer< long long >::TimerDays >().count()
			);
	}

	return 0;
}