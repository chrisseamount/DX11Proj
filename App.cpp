#include "App.h"
#include<sstream>
#include<iomanip>

App::App() : wnd(800, 600, "Window")
{
}

int App::Go()
{
	while (true)
	{
		if (const auto ecode = Window::ProcessMessages())
		{
			return *ecode;
		}
		DoFrame();
	}
}

void App::DoFrame()
{
	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	wnd.Gfx().ClearBuffer(1.0f-c*0.6f,1.0f- c*0.2f, 1.0f-c*0.1f);
	wnd.Gfx().DrawTestTriangle();
	wnd.Gfx().EndFrame();
	 
}
