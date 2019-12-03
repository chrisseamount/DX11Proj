#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include "win.h"
#include <d3d11.h>

class Graphics 
{
private:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* pTarget = nullptr;

public:
	Graphics(HWND hWnd);
	~Graphics();

	Graphics(const Graphics& other) = delete;
	Graphics(Graphics&& other) = delete;
	Graphics& operator=(const Graphics& other) = delete;
	Graphics& operator=(Graphics&& other) = delete;

	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;

};


#endif // !GRAPHICS_H_INCLUDED
