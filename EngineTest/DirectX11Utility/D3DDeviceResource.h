#pragma once

#include "IDevice.h"

class CD3DDeviceResource : public IDevice
{
public:
	CD3DDeviceResource() = delete;
	constexpr CD3DDeviceResource( HWND hWnd, int nScreenWidth, int nScreenHeight, bool bSync, bool bFullScreen, float fScreenDepth, float fScreenNear );
	~CD3DDeviceResource();

	virtual bool initialize()override;
	virtual bool finalize()override;

protected:

	HWND m_hWnd{ nullptr };
	int m_nScreenWidth{ 0 };
	int m_nScreenHeight{ 0 };
	bool m_bSync{ false };
	bool m_bFullScreen{ false };
	float m_fScreenDepth{ 0.0f };
	float m_fScreenNear{ 0.0f };
};

