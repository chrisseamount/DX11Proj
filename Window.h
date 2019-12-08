#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include"win.h"
#include"Exceptions.h"
#include"Keyboard.h"
#include"Mouse.h"
#include"Graphics.h"
#include<optional>
#include<memory>

class Window
{
public:
	class Exception : public Exceptions
	{
		using Exceptions::Exceptions;
	public:
		static std::string TranslateErrorCode(HRESULT hr) noexcept;

	};

	class HrException : public Exception
	{
	public:
		HrException(int line, const char* file, HRESULT hr) noexcept;
		~HrException() = default;

		HrException(const HrException& other) = default;
		HrException(HrException&& other) = default;
		HrException& operator=(const HrException& other) = default;
		HrException& operator=(HrException&& other) = default;

		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorDescription() const noexcept;

	private:
		HRESULT _hr;

	};

	class NoGfxException : public Exception
	{
	public:
		using Exception::Exception;
		const char* GetType() const noexcept override;

	};

private:
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;

	private:
		WindowClass() noexcept;
		~WindowClass();

		WindowClass(const WindowClass& other) = delete;
		WindowClass(WindowClass&& other) =  delete;
		WindowClass& operator=(const WindowClass& other) = delete;
		WindowClass& operator=(WindowClass&& other) = delete;

		static constexpr const char wndClassName[] = "Sample Window Class";
		static WindowClass wndClass;
		HINSTANCE hInst;

	};

public:
	Window(int width, int height, const char* name);
	~Window();

	Window(const Window& other) = delete;
	Window(Window&& other) = delete;
	Window& operator=(const Window& other) = delete;
	Window& operator=(Window&& other) = delete;

	void SetTitle(const std::string& title);
	static std::optional<int> ProcessMessages();

	Graphics& Gfx();

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

public:
	Keyboard kbd;
	Mouse mouse;

private:
	int _width;
	int _height;
	HWND hWnd;
	std::unique_ptr<Graphics> pGfx;

};

#endif // !WINDOW_H_INCLUDED