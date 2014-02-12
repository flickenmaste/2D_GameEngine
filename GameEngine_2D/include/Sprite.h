// Will Gilstrap - Game Engine
// 2/11/2014

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <SOIL.h>
#include <Entity.h>
#include <GLlog.h>

class Sprite : public Entity
{
public:
	GLuint VBO;	
	GLuint VAO;
	GLuint EBO;
	GLuint m_VertexShader;
	GLuint m_FragmentShader;
	GLuint shaderProgram;
	GLint uniTrans;
	GLuint textures[1];
	GLuint proj_location;
	GLuint view_location;
	glm::vec2 m_v2Scale;
	glm::vec3 m_v3Position;

	Sprite();
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
	void DrawTex(mat4 &translation, mat4 &Ortho);
	bool LoadVertShader(const char* filePath);
	bool LoadFragShader(const char* filePath);
	bool LinkShaders();

};

#endif