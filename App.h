#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include "Window.h"
#include "Timer.h"
#include "imgui/ImguiManager.h"
#include "Camera.h"
#include "PointLight.h"

class App
{
public:
	App();
	~App();

	App(const App & other) = default;
	App(App && other) = default;
	App& operator=(const App & other) = default;
	App& operator=(App && other) = default;

	int Go();

private:
	void DoFrame();

private:
	ImguiManager imgui;
	Window wnd;
	Timer timer;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	float speed_factor = 1.0f;
	Camera cam;
	PointLight light;
	static constexpr size_t nDrawables = 180;
};


#endif // !APP_H_INCLUDED
