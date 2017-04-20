#pragma once
class CWindowsApplication
{
public:
	CWindowsApplication() = delete;
	CWindowsApplication( HINSTANCE hInstance );
	~CWindowsApplication();

	static LRESULT CALLBACK staticWndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

	bool initialize() noexcept;
	bool finalize() noexcept;

	bool execute() noexcept;

private:

	HWND m_hWnd{ nullptr };
	HINSTANCE m_hInstance{ nullptr };
};