// Will Gilstrap - Game Engine
// 2/4/2014

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
	GLint uniTrans;
	GLuint textures[1];
	
	// Destructor
	~Sprite();

	void CreateTriangle();
	void CreateSquare();
	void CreateShaders();
	void Draw();
	void LoadTexture(const char * filename);
	void LoadTexture(const char * filename, mat4 &trans);	// to create a sprite that moves
	void LoadTexShaders();
	void LoadTexShaders(mat4 &translation);	// OLD
	void DrawTex();
	void DrawTex(mat4 &translation);

};

#endif