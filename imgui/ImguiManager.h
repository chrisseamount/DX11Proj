#ifndef IMGUI_MANAGER_H_INCLUDED
#define IMGUI_MANAGER_H_INCLUDED

class ImguiManager
{
public:
	ImguiManager();
	~ImguiManager();

	ImguiManager(const ImguiManager& other) = default;
	ImguiManager(ImguiManager&& other) = default;
	ImguiManager& operator=(const ImguiManager& other) = default;
	ImguiManager& operator=(ImguiManager&& other) = default;

};

#endif // !IMGUI_MANAGER_H_INCLUDED
