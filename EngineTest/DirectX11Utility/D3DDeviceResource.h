#pragma once

#include "IDevice.h"

#include <d3d11.h>

class CD3DDeviceResource : public IDevice
{
public:
	CD3DDeviceResource() = delete;
	CD3DDeviceResource( HWND hWnd, int nScreenWidth, int nScreenHeight, bool bSync, bool bFullScreen, float fScreenDepth, float fScreenNear );
	~CD3DDeviceResource();

	virtual bool initialize() override;
	virtual bool finalize() override;

	void setClearCalor( float fR, float fG, float fB, float fA ) noexcept
	{
		m_fClearColor[0] = fR;
		m_fClearColor[1] = fG;
		m_fClearColor[2] = fB;
		m_fClearColor[3] = fA;
	}

	void clearRenderTargetView()
	{
		m_pd3dDeviceContext->ClearRenderTargetView( m_pd3dRenderTargetView, m_fClearColor );
	}

	void present()
	{
		m_pSwapChain->Present( 0, 0 );
	}

protected:

	HWND m_hWnd{ nullptr };
	int m_nScreenWidth{ 0 };
	int m_nScreenHeight{ 0 };
	bool m_bSync{ false };
	bool m_bFullScreen{ false };
	float m_fScreenDepth{ 0.0f };
	float m_fScreenNear{ 0.0f };

	ID3D11Device* m_pd3dDevice{ nullptr };
	ID3D11DeviceContext* m_pd3dDeviceContext{ nullptr };
	IDXGISwapChain* m_pSwapChain{ nullptr };
	ID3D11RenderTargetView* m_pd3dRenderTargetView{ nullptr };

	D3D_DRIVER_TYPE m_DriverType{ D3D_DRIVER_TYPE_UNKNOWN };
	D3D_FEATURE_LEVEL m_FeatureLevel{ D3D_FEATURE_LEVEL_11_0 };

	float m_fClearColor[4]{ 0.0f, 0.125f, 0.3f, 1.0f };
};

