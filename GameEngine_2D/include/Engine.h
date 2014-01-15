// Will Gilstrap - Game Engine
// 1/15/2013

#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glfw.h>
#include <FreeImage.h>
#include <XML.h>
#include <XML2.h>
#include <as.h>
#include <GameStates.h>
#include <Entity.h>
//#include <FMODwrapper.h>
#include <Mathlib.h>
#include <cstdio>
#include <vector>
#include <stack>
#include <memory>

using std::stack;
using std::unique_ptr;

static class Engine
{
private:
	stack<unique_ptr<States>>StateStack;

public:
	struct V_2i_4f 
	{ 
		int iVertices[2]; 
		float fColours[4]; 
	}; 

	Engine();	// Constructor - call functions to start up engine - scripts - XML
	~Engine();	// Destructor - close everything

	// Open GL
	static int GLFWCALL windowCloseListener(); // Check for window close
	static int openWindow(); // Open OpenGL window
	static unsigned int LoadTexture(const char* a_szTexture, unsigned int a_uiFormat /* = GL_RGBA */); // Load texture

	// State stack
	void AddStack();	// Add to the stack
	void UpdateStack();	// Update the stack




};


#endif