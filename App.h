#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include "Window.h"
#include "Timer.h"

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
	Window wnd;
	Timer timer;
	std::vector<std::unique_ptr<class Box>> boxes;
};


#endif // !APP_H_INCLUDED
