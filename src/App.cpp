#include "App.hpp"

App::App(){
  Engine::Log("Object Made");
}
App::~App(){
  Engine::Log("Object Destroyed");
}

void App::Run(){
  if (appState == AppState::ON)
    Engine::FatalError("App already running.");
  
  Engine::Init();

  unsigned int windowFlags = 0;

  //windowFlags |= Engine::WindowFlags::FULLSCREEN;

  //windowFlags |= Engine::WindowFlags::BORDERLESS;

  window.Create("Engine", 800, 600, windowFlags);
  
  Load();

  appState = AppState::ON;

  Loop();
}

void App::Load(){}
void App::Loop()
{
  while(appState == AppState::ON)
  {
    Update();
    Draw();
    // Get SDL to swap our buffer
    window.SwapBuffer();
    LateUpdate();
    FixedUpdate(0.0f);
    InputUpdate();
  }
}
void App::Update(){}
void App::Draw(){}
void App::LateUpdate(){}
void App::FixedUpdate(float _delta_time){}
void App::InputUpdate()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      appState = AppState::OFF;
      break;
    case SDL_MOUSEMOTION:
      break;
    case SDL_KEYUP:
      break;
    case SDL_KEYDOWN:
      break;
    }
  }
}