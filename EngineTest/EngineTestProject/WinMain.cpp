// EngineTestProject2.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
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