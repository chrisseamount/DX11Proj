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
	public:
		Exception(int line, const char* file, HRESULT hr) noexcept;
		~Exception() = default;

		Exception(const Exception& other) = default;
		Exception(Exception&& other) = default;
		Exception& operator=(const Exception& other) = default;
		Exception& operator=(Exception&& other) = default;

		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;

	private:
		HRESULT _hr;

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

#define WND_EXCEPT(hr) Window::Exception(__LINE__,__FILE__,hr)
#define WND_LAST_EXCEPT() Window::Exception(__LINE__,__FILE__,GetLastError())

#endif // !WINDOW_H_INCLUDED