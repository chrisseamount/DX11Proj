#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include "win.h"
#include "Exceptions.h"
#include <d3d11.h>
#include <wrl.h>
#include <vector>
#include "DxgiInfoManager.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include<memory>
#include <random>

class Graphics 
{
	friend class Bindable;

public:
	class Exception : public Exceptions
	{
	public:
		using Exceptions::Exceptions;

	};

	class HrException : public Exception
	{
	public:
		HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs = {}) noexcept;
		~HrException() = default;

		HrException(const HrException & other) = default;
		HrException(HrException && other) = default;
		HrException& operator=(const HrException & other) = default;
		HrException& operator=(HrException && other) = default;

		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
		std::string GetErrorDescription() const noexcept;
		std::string GetErrorInfo() const noexcept;

	private:
		HRESULT _hr;
		std::string info;

	};

	class InfoException : public Exception
	{
	public:
		InfoException(int line, const char* file, std::vector<std::string> infoMsgs = {}) noexcept;
		~InfoException() = default;

		InfoException(const InfoException& other) = default;
		InfoException(InfoException&& other) = default;
		InfoException& operator=(const InfoException& other) = default;
		InfoException& operator=(InfoException&& other) = default;

		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorInfo() const noexcept;

	private:
		std::string info;

	};

	class DeviceRemovedException : public HrException
	{
		using HrException::HrException;

	public:
		const char* GetType() const noexcept override;

	private:
		std::string reason;

	};

public:
	Graphics(HWND hWnd);
	~Graphics() = default;

	Graphics(const Graphics& other) = delete;
	Graphics(Graphics&& other) = delete;
	Graphics& operator=(const Graphics& other) = delete;
	Graphics& operator=(Graphics&& other) = delete;

	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;
	void DrawIndexed(UINT count) noexcept;
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;
	void DrawTestTriangle(float angle, float x, float y);

private:
	DirectX::XMMATRIX projection;

#ifndef NDEBUG
	DxgiInfoManager infoManager;
#endif // !NDEBUG
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;


};


#endif // !GRAPHICS_H_INCLUDED
