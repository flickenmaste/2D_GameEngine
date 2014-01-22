// Will Gilstrap - Game Engine
// 1/21/2013

#include <Engine.h>
#include <Sprite.h>

void Sprite::CreateTriangle()
{
	// Make stuff
	float points[] =
	{
		0.0f, 0.5f, 0.0f,
		0.5f,-0.5f, 0.0f,
		-0.5f,-0.5f, 0.0f,
	};
	this->VBO = 0;
	glGenBuffers (1, &VBO);
	glBindBuffer (GL_ARRAY_BUFFER, VBO);
	glBufferData (GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
	this->VAO = 0;
	glGenVertexArrays (1, &VAO);
	glBindVertexArray (VAO);
	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
}

void Sprite::CreateSquare()
{
	// Make stuff
	float points[] =
	{
		-0.5f,  0.5f, 1.0f,
		0.5f,  0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,

		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 1.0f,
		-0.5f,  0.5f, 1.0f,
	};
	this->VBO = 0;
	glGenBuffers (1, &VBO);
	glBindBuffer (GL_ARRAY_BUFFER, VBO);
	glBufferData (GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	this->VAO = 0;
	glGenVertexArrays (1, &VAO);
	glBindVertexArray (VAO);
	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
}

void Sprite::CreateShaders()
{

	const char* vertex_shader =
		"#version 330\n"
		"in vec3 vp;"
		"void main() {"
		"gl_Position = vec4 (vp, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 330\n"
		"out vec4 frag_colour;"
		"void main() {"
		"frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
		"}";

	// Create a shader
	GLuint vs = glCreateShader (GL_VERTEX_SHADER);
	// Put the char* into the shader
	glShaderSource (vs, 1, &vertex_shader, NULL);
	// Compile the shader
	glCompileShader (vs);
	//printShaderInfoLog(vs);
	GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (fs, 1, &fragment_shader, NULL);
	glCompileShader (fs);
	//printShaderInfoLog(fs);
	// Create the container that holders your shaders
	this->shaderProgram = glCreateProgram();
	// Attach the shaders you compiled
	glAttachShader (this->shaderProgram, fs);
	glAttachShader (this->shaderProgram, vs);
	// This links the shaders together, like compile
	glLinkProgram (this->shaderProgram);
	//printProgramInfoLog(shaderProgram);
}