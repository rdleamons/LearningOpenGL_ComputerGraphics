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

  // Toggles full screen or borderless
  //windowFlags |= Engine::WindowFlags::FULLSCREEN;

  //windowFlags |= Engine::WindowFlags::BORDERLESS;

  window.Create("Engine", 800, 600, windowFlags);
  
  Load();

  appState = AppState::ON;

  Loop();
}

void App::Load()
{
  // Build and compile our shader program
  // Vertex shader:
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER); // Claim a shader spot on the GPU
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  // Check for shader compilation errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl; // Change later
  }

  // Fragment Shader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  // Check for shader compilation errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  // Link shaders
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // Check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if(!success)
  {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  float vertices[] = {
    -0.5f, -0.5f, 0.0f, // Left vertex
     0.5f, -0.5f, 0.0f, // Right vertex
     0.0f, 0.5f, 0.0f   // Top vertex
  };

  // VBO, VAO, 
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  //

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0); // Unbinding the array
}

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

void App::Draw()
{
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // Be sure to activatethe shader program before calling any uniforms
  glUseProgram(shaderProgram);

  // Update shader uniform 
  double timeVal = SDL_GetTicks() / 1000;
  float greenVal = static_cast<float>(sin(timeVal) / 2.0 + 0.5f);

  // Get uniform location
  int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
  
  // Set the uniform
  glUniform4f(vertexColorLocation, 0.0f, greenVal, 0.0f, 1.0f);

  // Render triangle
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0); // Unbinding the array

}

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