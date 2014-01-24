// Will Gilstrap - Game Engine
// 1/23/2014

#ifndef __INPUT_H__
#define __INPUT_H__

#include <Engine.h>

class Input : public Sprite
{
public:	
	static void Rotate(GLFWwindow* window, Sprite &s, mat4 &trans);
	static void Move(GLFWwindow* window, Sprite &s, mat4 &trans);
	static void Scale(GLFWwindow* window, Sprite &s, mat4 &trans);

};

#endif