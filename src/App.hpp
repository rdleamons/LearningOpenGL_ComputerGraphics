#include <iostream>
#include <SDL.h>
#include <math.h>

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

	// Later, move outside of App class
	unsigned int shaderProgram;
	unsigned int VBO, VAO; // Vertex buffer & attributes

	const char *vertexShaderSource = "#version 330 core\n" // What version of OpenGL do we want to be compatible with?
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

	// Runs for however many pixels in the screen are being drawn in, and is called once per frame. 
    const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
	"uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = ourColor;\n"
    "}\0";
};