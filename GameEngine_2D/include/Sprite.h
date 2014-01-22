// Will Gilstrap - Game Engine
// 1/21/2013

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <Entity.h>

class Sprite : public Entity
{
public:
	GLuint VBO;	
	GLuint VAO;
	GLuint EBO;
	GLuint shaderProgram;
	

	void CreateTriangle();
	void CreateSquare();
	void CreateShaders();

};

#endif