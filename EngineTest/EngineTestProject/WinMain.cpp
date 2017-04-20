// EngineTestProject2.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include "WindowsApplication.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	CWindowsApplication SampleApplication( hInstance );

	if( !SampleApplication.initialize() )
		return 0;

	if( !SampleApplication.execute() )
	{
		SampleApplication.finalize();
		return 0;
	}

	SampleApplication.finalize();

	return 0;
}