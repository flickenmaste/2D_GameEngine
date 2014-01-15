// Will Gilstrap - Game Engine
// 1/14/2013

#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glfw.h>
#include <FreeImage.h>
#include <XML.h>
#include <XML2.h>
#include <as.h>
//#include <FMODwrapper.h>
#include <Mathlib.h>
#include <cstdio>

static class Engine
{
public:
	struct V_2i_4f 
	{ 
		int iVertices[2]; 
		float fColours[4]; 
	}; 

	static int GLFWCALL windowCloseListener();
	static int openWindow();
	unsigned int LoadTexture(const char* a_szTexture, unsigned int a_uiFormat /* = GL_RGBA */);

};


#endif