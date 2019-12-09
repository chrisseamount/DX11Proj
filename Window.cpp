#include"Window.h"
#include <sstream>
#include "resource.h"
#include "Macros/WindowsThrowMacros.h"
#include "imgui/imgui_impl_win32.h"

Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept: hInst(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };

	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hIcon = static_cast<HICON>(LoadImage(hInst,MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,32,32,0));
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	wc.hIconSm = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0));

	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, GetInstance());
}


const char * Window::WindowClass::GetName() noexcept
{
	return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return wndClass.hInst;
}

Window::Window(int width, int height, const char* name) : _width(width), _height(height)
{
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	if (AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE) == 0)
	{
		throw WND_LAST_EXCEPT();
	}
	
	hWnd = CreateWindow(
		WindowClass::GetName(),												   // Window class
		name,																   // Window text
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,							   // Window style
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left , wr.bottom - wr.top, // Size and position
		nullptr,															   // Parent window    
		nullptr,															   // Menu
		WindowClass::GetInstance(),											   // Instance handle
		this																   // Additional application data
	);

	// checks for error
	if (hWnd == nullptr)
	{
		throw WND_LAST_EXCEPT();
	}

	// newly created window starts off hidden
	ShowWindow(hWnd, SW_SHOWDEFAULT);

	// Init ImGui Win32 Impl
	ImGui_ImplWin32_Init(hWnd);

	//create graphics object
	pGfx = std::make_unique<Graphics>(hWnd);

}

Window::~Window()
{
	ImGui_ImplWin32_Shutdown();
	DestroyWindow(hWnd);
}

void Window::SetTitle(const std::string& title)
{
	if (SetWindowText(hWnd, title.c_str()) == 0)
	{
		throw WND_LAST_EXCEPT();
	}
}

std::optional<int> Window::ProcessMessages()
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0,PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return msg.wParam;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return {};
}

Graphics& Window::Gfx()
{
	if (!pGfx)
	{
		throw WND_NOGFX_EXCEPT();
	}
	return *pGfx;
}

LRESULT Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// Use create parameter passed in from CreateWindow() to strre window class pointer at WinAPI
	if (msg == WM_NCCREATE)
	{
		// Extract pointer to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);

		// Set WinApi-managed user data to store pointer to window class
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// Set message proc to normal (non-setup) handler now that the setup is finished
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		// Forward the message to window class handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}

	// If we get a message before the WM_NCCREATE message, handle with default handler
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// Retrive pointer to window class
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	// Forward message to window class handler
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
	{
		return true;
	}
	const auto imio = ImGui::GetIO();
	
	switch (msg)
	{
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	case WM_KILLFOCUS:
	{
		kbd.ClearState();
		break;
	}

// *********************************************************************
// KEYBOARD MESSAGES
// *********************************************************************
	
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	{
		if (imio.WantCaptureKeyboard)
		{
			break;
		}
		
		if (!(lParam & 0x40000000) || kbd.AutorepeatIsEnabled())
		{
			kbd.OnKeyPressed(static_cast<unsigned char>(wParam));
		}
		break;
	}

	case WM_KEYUP:
	case WM_SYSKEYUP:
	{
		if (imio.WantCaptureKeyboard)
		{
			break;
		}
		
		kbd.OnKeyReleased(static_cast<unsigned char>(wParam));
		break;
	}

	case WM_CHAR:
	{
		if (imio.WantCaptureKeyboard)
		{
			break;
		}
		
		kbd.OnChar(static_cast<unsigned char>(wParam));
		break;
	}

// *********************************************************************
// MOUSE MESSAGES
// *********************************************************************

	case WM_MOUSEMOVE:
	{
		if (imio.WantCaptureMouse)
		{
			break;
		}
		
		const POINTS pt = MAKEPOINTS(lParam);
		if (pt.x >= 0 && pt.x < _width && pt.y >= 0 && pt.y < _height)
		{
			mouse.OnMouseMove(pt.x, pt.y);
			if (!mouse.IsInWindow())
			{
				SetCapture(hWnd);
				mouse.OnMouseEnter();
			}
		}
		else
		{
			if (wParam & (MK_LBUTTON | MK_RBUTTON))
			{
				mouse.OnMouseMove(pt.x, pt.y);
			}
			else
			{
				ReleaseCapture();
				mouse.OnMouseLeave();
			}
		}
		break;
	}

	case WM_LBUTTONDOWN:
	{
		if (imio.WantCaptureMouse)
		{
			break;
		}
		
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnLeftPressed(pt.x, pt.y);
		break;
	}
		
	case WM_RBUTTONDOWN:
	{
		if (imio.WantCaptureMouse)
		{
			break;
		}
		
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnRightPressed(pt.x, pt.y);
		break;
	}

	case WM_LBUTTONUP:
	{
		if (imio.WantCaptureMouse)
		{
			break;
		}
		
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnLeftReleased(pt.x, pt.y);
		break;
	}

	case WM_RBUTTONUP:
	{
		if (imio.WantCaptureMouse)
		{
			break;
		}
		
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnRightReleased(pt.x, pt.y);
		break;
	}

	case WM_MOUSEWHEEL:
		if (imio.WantCaptureMouse)
		{
			break;
		}
		
		const POINTS pt = MAKEPOINTS(lParam);
		const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
		mouse.OnWheelDelta(pt.x, pt.y, delta);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}


Window::HrException::HrException(int line, const char* file, HRESULT hr) noexcept 
	: 
	Exception(line, file),
	_hr(hr)
{}

const char* Window::HrException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
		<< std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
		<< "[Description]" << GetErrorDescription() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Window::HrException::GetType() const noexcept
{
	return "Window Exception";
}

std::string Window::Exception::TranslateErrorCode(HRESULT hr) noexcept
{
	char* pMsgBuf = nullptr;
	DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr
	);
	if (nMsgLen == 0)
	{
		return "Unidentified error code";
	}
	std::string errorString = pMsgBuf;
	LocalFree(pMsgBuf);
	return errorString;
}

HRESULT Window::HrException::GetErrorCode() const noexcept
{
	return _hr;
}

std::string Window::HrException::GetErrorDescription() const noexcept
{
	return Exception::TranslateErrorCode(_hr);
}

const char* Window::NoGfxException::GetType() const noexcept
{
	return "Window Exception [No Graphics]";
}
