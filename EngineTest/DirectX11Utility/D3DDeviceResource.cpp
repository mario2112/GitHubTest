#include "stdafx.h"
#include "D3DDeviceResource.h"

CD3DDeviceResource::CD3DDeviceResource( HWND hWnd, int nScreenWidth, int nScreenHeight, bool bSync, bool bFullScreen, float fScreenDepth, float fScreenNear )
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
	HRESULT hr = S_OK;

	auto nCreateDeviceFlags{ 0 };
#if defined( _DEBUG )
	nCreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // #if defined( _DEBUG )

	D3D_DRIVER_TYPE arrDriverTypes[]{ D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_REFERENCE };
	UINT nNumDriverType = ARRAYSIZE( arrDriverTypes );

	D3D_FEATURE_LEVEL arrFeatureLevels[]{ D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };
	UINT nNumFeatureLevels = ARRAYSIZE( arrFeatureLevels );

	DXGI_SWAP_CHAIN_DESC sd;
	memset( &sd, 0, sizeof( DXGI_SWAP_CHAIN_DESC ) );
	sd.BufferCount = 1;
	sd.BufferDesc.Width = m_nScreenWidth;
	sd.BufferDesc.Height = m_nScreenHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = m_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = !m_bFullScreen;

	for( UINT i = 0 ; i < nNumDriverType ; ++i )
	{
		m_DriverType = arrDriverTypes[i];
		hr = D3D11CreateDeviceAndSwapChain( nullptr, m_DriverType, nullptr, nCreateDeviceFlags, arrFeatureLevels, nNumFeatureLevels, 
			D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pd3dDevice, &m_FeatureLevel, &m_pd3dDeviceContext );

		if( SUCCEEDED( hr ) )
			break;
	}

	if( FAILED( hr ) )
		return false;

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
	if( FAILED( hr ) )
		return false;

	hr = m_pd3dDevice->CreateRenderTargetView( pBackBuffer, nullptr, &m_pd3dRenderTargetView );
	pBackBuffer->Release();
	if( FAILED( hr ) )
		return false;

	m_pd3dDeviceContext->OMSetRenderTargets( 1, &m_pd3dRenderTargetView, nullptr );

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = static_cast< FLOAT >( m_fScreenDepth );
	vp.Height = static_cast< FLOAT >( m_fScreenDepth );
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pd3dDeviceContext->RSSetViewports( 1, &vp );

	return true;
}

bool CD3DDeviceResource::finalize()
{
	if( m_pd3dDeviceContext )
		m_pd3dDeviceContext->ClearState();

	D3D_SAFE_RELEASE( m_pd3dRenderTargetView );
	D3D_SAFE_RELEASE( m_pSwapChain );
	D3D_SAFE_RELEASE( m_pd3dDeviceContext );
	D3D_SAFE_RELEASE( m_pd3dDevice );

	return true;
}