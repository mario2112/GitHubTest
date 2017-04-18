#include "stdafx.h"
#include "AsyncInputCommand.h"

void SampleInput( ICommand::enKeyState KeyState )
{
	printf( "Success Callback SampleInput\n" );
}

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow )
{
	CAsyncInputCommand Test( VK_LEFT, SampleInput );

	Test.execute();

	return 0;
}