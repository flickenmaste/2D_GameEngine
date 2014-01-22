// Will Gilstrap - Game Engine
// 1/22/2013

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <SOIL.h>
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
	void Draw();
	void LoadTexture(const char * filename);
	void LoadTexShaders();
	void LoadTexShaders(Matrix4 &translation);
	void DrawTex();

};

#endif