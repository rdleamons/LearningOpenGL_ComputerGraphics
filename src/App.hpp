#include <iostream>
#include <SDL.h>

#include "Engine/Engine.hpp"
#include "Engine/Debug.hpp"
#include "Engine/Window.hpp"

enum AppState
{
	ON,
	OFF
};

class App
{
public:
	App();
	~App();

	void Run();

private:
	void Load();
	void Loop();
	void Update();
	void Draw();
	void LateUpdate();
	void FixedUpdate(float _delta_time);
	void InputUpdate();

	AppState appState = AppState::OFF;

	Engine::Window window;
};