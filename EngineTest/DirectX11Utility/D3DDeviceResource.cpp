#include "stdafx.h"
#include "D3DDeviceResource.h"

constexpr CD3DDeviceResource::CD3DDeviceResource( HWND hWnd, int nScreenWidth, int nScreenHeight, bool bSync, bool bFullScreen, float fScreenDepth, float fScreenNear )
	:	m_hWnd( hWnd )
	,	m_nScreenWidth( nScreenWidth )
	,	m_nScreenHeight( nScreenHeight )
	,	m_bSync( bSync )
	,	m_bFullScreen( bFullScreen )
	,	m_fScreenDepth( fScreenDepth )
	,	m_fScreenNear( fScreenNear )
{
}

CD3DDeviceResource::~CD3DDeviceResource()
{
}

bool CD3DDeviceResource::initialize()
{
	return true;
}

bool CD3DDeviceResource::finalize()
{
	return true;
}