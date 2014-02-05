// Will Gilstrap - Game Engine
// 2/4/2014

#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <GL\glew.h>
#define GLFW_DLL
#include <GL\glfw3.h>
#include <stdio.h>
#include <XML.h>
#include <XML2.h>
#include <as.h>
#include <GameStates.h>
#include <Sprite.h>
#include <Input.h>
#include <Text.h>
//#include <FMODwrapper.h>
#include <glm.hpp>
#include <GLlog.h>
#include <cstdio>
#include <vector>
#include <stack>
#include <memory>

using std::stack;
using std::unique_ptr;
using glm::mat4;
using glm::vec4;
using glm::vec3;

static class Engine
{
private:
	stack<unique_ptr<States>>StateStack;

public:
	GLFWwindow * window;
	
	Engine();	// Constructor - call functions to start up engine - scripts - XML
	~Engine();	// Destructor - close everything

	// Open GL
	unsigned int OpenWindow();
	void RunGame();

	void glfw_window_size_callback (GLFWwindow* window, int width, int height);

	// Draw FPS
	void _update_fps_counter (GLFWwindow* window);

	// State stack
	void AddStack();	// Add to the stack
	void UpdateStack();	// Update the stack




};

#endif