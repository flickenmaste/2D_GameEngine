// Will Gilstrap - Game Engine
// 2/11/2014

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <GL\glew.h>
#include <GLlog.h>
#include <TextFileReader.h>
#include <Vector2.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

using glm::mat4;
using glm::vec2;
using glm::vec3;
using glm::vec4;

struct Vertex
{
	union
	{
	struct 
		{
			vec3 Pos;
			vec4 Color;
			vec2 UV;
		};
		
		struct
		{
			float X, Y, Z;
			float R, G, B, A;
			float U, V;
		};
	};
	

	bool operator == (const Vertex& rhs)
	{
		return (X == rhs.X && Y == rhs.Y && Z == rhs.Z && U == rhs.U && V == rhs.V && R == rhs.R && G == rhs.G && B == rhs.B && A == rhs.A );
	}
};

extern mat4 * Ortho;

class Entity
{
public:
	Entity(void);
	~Entity(void);

	GLuint m_VBO;
	GLuint m_VAO;
	GLuint m_EBO;
	
	GLuint m_FragmentShader;
	GLuint m_VertexShader;

	GLuint m_ShaderProgram;

	float m_afArray[16];

	void Draw();
	bool LoadVertShader(const char*);
	bool LoadFragShader(const char*);
	bool LinkShaders();
};

#endif