#include "stdafx.h"
#include "WindowsApplication.h"

CWindowsApplication::CWindowsApplication( HINSTANCE hInstance )
	:	m_hInstance( hInstance )
{
}

CWindowsApplication::~CWindowsApplication()
{
}

LRESULT CALLBACK CWindowsApplication::staticWndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
		case WM_CREATE:
			break;

		case WM_DESTROY:
			PostQuitMessage( 0 );
			break;
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}

bool CWindowsApplication::initialize() noexcept
{
	if( !m_hInstance )
		return false;

	WNDCLASS wndClass;
	memset( &wndClass, 0, sizeof( WNDCLASS ) );
	wndClass.hInstance = m_hInstance;
	wndClass.hbrBackground = ( HBRUSH )GetStockObject( WHITE_BRUSH );
	wndClass.hCursor = LoadCursor( NULL, IDC_ARROW );
	wndClass.hIcon = LoadIcon( NULL, IDI_APPLICATION );
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = staticWndProc;
	wndClass.lpszClassName = L"SampleEngine";

	RegisterClass( &wndClass );

	LPCWSTR lpszClass = L"SampleEngine";
	m_hWnd = CreateWindow( lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, m_hInstance, nullptr );
	if( !m_hWnd )
		return false;

	ShowWindow( m_hWnd, SW_SHOW );
	UpdateWindow( m_hWnd );

	return true;
}

bool CWindowsApplication::finalize() noexcept
{
	DestroyWindow( m_hWnd );
	return true;
}

bool CWindowsApplication::execute() noexcept
{
	if( !m_hWnd )
		return false;

	MSG msg;
	memset( &msg, 0, sizeof( msg ) );

	while( true )
	{
		bool bResult = PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) ? true : false;
		if( WM_QUIT == msg.message )
			return false;

		if(  bResult )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
		}
	}

	return true;
}