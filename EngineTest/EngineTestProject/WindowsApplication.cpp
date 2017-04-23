#include "stdafx.h"
#include "WindowsApplication.h"

#include "D3DDeviceResource.h"

CD3DDeviceResource* g_TestResource = nullptr;

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
	m_hWnd = CreateWindow( lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, 0, 0, 1024, 768, nullptr, nullptr, m_hInstance, nullptr );
	if( !m_hWnd )
		return false;

	ShowWindow( m_hWnd, SW_SHOW );
	UpdateWindow( m_hWnd );

	g_TestResource = new CD3DDeviceResource( m_hWnd, 1024, 768, true, false, 1, 1 );
	g_TestResource->initialize();

	return true;
}

bool CWindowsApplication::finalize() noexcept
{
	DestroyWindow( m_hWnd );

	g_TestResource->finalize();
	delete g_TestResource;

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
			g_TestResource->clearRenderTargetView();
			g_TestResource->present();
		}
	}

	return true;
}