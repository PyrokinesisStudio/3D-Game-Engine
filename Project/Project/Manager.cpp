//Needs header file
#include "Manager.h"
#include "Externs.h"

//Engien specific
#include <Engine\Input.h>
#include <Engine\Console.h>

//Create memory for window
GLFWwindow *win;

//Setup all of the program
void Manager::init() 
{
	//Init GLFW
	GLboolean init_status = glfwInit();

	if (!init_status) Console::error("Could not initialize GLFW.");

	//Try to use OPEN GL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Only use modern OPEN GL (All legacy functions will return an error)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Non resizable window
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//All GLFW error messages go though error class
	glfwSetErrorCallback(Console::glfwError);

	//Create window based on externs
	win = glfwCreateWindow(GAME_WIDTH, GAME_HEIGHT, GAME_TITLE, NULL, NULL);
	if (!win) Console::error("Could not create the game window.");

	//Make OPEN GL context
	glfwMakeContextCurrent(win);
	
	//Init GLEW
	GLenum glewStatus = glewInit();

	if (glewStatus != GLEW_OK) Console::error("GLEW failed to setup.");

	//Make sure events are passed though engine input manager
	glfwSetKeyCallback(win, Input::keyCallback);
	glfwSetCursorPosCallback(win, Input::cursorCallback);
	glfwSetMouseButtonCallback(win, Input::mouseClickCallback);

	//State can now be changed
	state = programState::Running;

	//Test console message
	Console::message("Started program...");
}

//Start of update
void Manager::clear() {}

//Main game logic
void Manager::logic() {}

//Get input from user
void Manager::input() 
{
	//Make sure all events are read
	glfwPollEvents();

	//Close on escape
	if (Input::getKey(GLFW_KEY_ESCAPE).released) quit();
}

//Draw the game using engine
void Manager::draw() {}

//Any post drawing things
void Manager::late()
{
	//Set stae of program
	if (glfwWindowShouldClose(win)) state = programState::Closing;

	//Update input manager
	Input::update();
}

//Close and clean up memory
void Manager::quit() 
{
	//Destroy class objects
	glfwDestroyWindow(win);

	//Close window
	glfwTerminate();

	//Set staet to break out of loop
	state = programState::Closing;
}