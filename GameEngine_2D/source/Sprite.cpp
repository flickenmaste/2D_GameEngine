// Will Gilstrap - Game Engine
// 2/11/2014

#include <Engine.h>
#include <Sprite.h>

Sprite::Sprite()
{

}

Sprite::~Sprite()
{
	glDeleteProgram(shaderProgram);
	
	glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);

    glDeleteVertexArrays(1, &VAO);
}

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
	printShaderInfoLog(vs);
	GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (fs, 1, &fragment_shader, NULL);
	glCompileShader (fs);
	printShaderInfoLog(fs);
	// Create the container that holders your shaders
	this->shaderProgram = glCreateProgram();
	// Attach the shaders you compiled
	glAttachShader (this->shaderProgram, fs);
	glAttachShader (this->shaderProgram, vs);
	// This links the shaders together, like compile
	glLinkProgram (this->shaderProgram);
	printProgramInfoLog(shaderProgram);
}

void Sprite::Draw()
{

	glUseProgram (this->shaderProgram);
	glBindVertexArray (this->VAO);
	// draw points 0-3 from the currently bound VAO with current in-use shader
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);

}

void Sprite::LoadTexture(const char * filename)
{

	// Shader sources
	const GLchar* vertexSource =
		"#version 330 core\n"
		"in vec3 position;"
		"in vec3 color;"
		"uniform mat4 trans;"
		"out vec3 Color;"
		"void main() {"
		"   Color = color;"
		"   gl_Position = trans * vec4(position, 1.0);"
		"}";
	const GLchar* fragmentSource =
		"#version 330 core\n"
		"in vec3 Color;"
		"in vec2 Texcoord;"
		"out vec4 outColor;"
		"uniform sampler2D texKitten;"
		"void main() {"
		"   outColor = texture(texKitten, Texcoord) * vec4(Color, 1.0);"
		"}";
	
	// Create Vertex Array Object
	this->VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create a Vertex Buffer Object and copy the vertex data to it
	this->VBO;
	glGenBuffers(1, &VBO);

	GLfloat vertices[] = {
		//  Position   Color             Texcoords
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
		0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create an element array
	this->EBO;
	glGenBuffers(1, &EBO);

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	// Load textures
	GLuint textures[1];
	glGenTextures(1, textures);

	int width, height;
	unsigned char* image;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glUniform1i(glGetUniformLocation(shaderProgram, "texKitten"), 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

}

void Sprite::LoadTexture(const char * filename, mat4 &trans)
{

	// Shader sources
	const GLchar* vertexSource =
		"#version 330 core\n"
		"in vec2 position;"
		"in vec3 color;"
		"in vec2 texcoord;"
		"uniform mat4 model;"
		"uniform mat4 projection;"
		"uniform mat4 view;"
		"out vec3 Color;"
		"out vec2 Texcoord;"
		"void main() {"
		"   Color = color;"
		"	Texcoord = texcoord;"
		"   gl_Position = model * vec4(position, 0.0, 1.0);"
		"}";
	const GLchar* fragmentSource =
		"#version 330 core\n"
		"in vec3 Color;"
		"in vec2 Texcoord;"
		"out vec4 outColor;"
		"uniform sampler2D texKitten;"
		"void main() {"
		"   outColor = texture(texKitten, Texcoord) * vec4(Color, 1.0);"
		"}";
	
	// Create Vertex Array Object
	this->VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create a Vertex Buffer Object and copy the vertex data to it
	this->VBO;
	glGenBuffers(1, &VBO);

	GLfloat vertices[] = {
		//  Position   Color             Texcoords
		-0.3f,  0.3f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
		0.3f,  0.3f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
		0.3f, -0.3f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
		-0.3f, -0.3f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create an element array
	this->EBO;
	glGenBuffers(1, &EBO);

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	// Create and compile the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Create and compile the fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// Link the vertex and fragment shader into a shader program
	this->shaderProgram = glCreateProgram();
	glAttachShader(this->shaderProgram, vertexShader);
	glAttachShader(this->shaderProgram, fragmentShader);
	glBindFragDataLocation(this->shaderProgram, 0, "outColor");
	glLinkProgram(this->shaderProgram);
	glUseProgram(this->shaderProgram);

	printShaderInfoLog(vertexShader);
	printShaderInfoLog(fragmentShader);
	printProgramInfoLog(this->shaderProgram);

	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation(this->shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);

	GLint colAttrib = glGetAttribLocation(this->shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	GLint texAttrib = glGetAttribLocation(this->shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

	proj_location = glGetUniformLocation (this->shaderProgram, "projection");
	
	view_location = glGetUniformLocation (this->shaderProgram, "view");
	
	// Load textures
	glGenTextures(1, this->textures);

	int width, height;
	unsigned char* image;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textures[0]);
	image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glUniform1i(glGetUniformLocation(shaderProgram, "texKitten"), 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	this->uniTrans = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(this->uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

	glBindTexture(GL_TEXTURE_2D, NULL);
}

void Sprite::LoadTexShaders()
{

	// Shader sources
	const GLchar* vertexSource =
		"#version 330 core\n"
		"in vec2 position;"
		"in vec3 color;"
		"in vec2 texcoord;"
		"out vec3 Color;"
		"out vec2 Texcoord;"
		"void main() {"
		"   Color = color;"
		"   Texcoord = texcoord;"
		"   gl_Position = vec4(position, 0.0, 1.0);"
		"}";
	const GLchar* fragmentSource =
		"#version 330 core\n"
		"in vec3 Color;"
		"in vec2 Texcoord;"
		"out vec4 outColor;"
		"uniform sampler2D texKitten;"
		"void main() {"
		"   outColor = texture(texKitten, Texcoord) * vec4(Color, 1.0);"
		"}";


	// Create and compile the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Create and compile the fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// Link the vertex and fragment shader into a shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	printShaderInfoLog(vertexShader);
	printShaderInfoLog(fragmentShader);
	printProgramInfoLog(shaderProgram);

	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

}

// Translate matrix shader - OLD
void Sprite::LoadTexShaders(mat4 &trans)
{

	// Shader sources
	const GLchar* vertexSource =
		"#version 330 core\n"
		"in vec3 position;"
		"in vec3 color;"
		"uniform mat4 trans;"
		"out vec3 Color;"
		"void main() {"
		"   Color = color;"
		"   gl_Position = trans * vec4(position, 1.0);"
		"}";
	const GLchar* fragmentSource =
		"#version 330 core\n"
		"in vec3 Color;"
		"in vec2 Texcoord;"
		"out vec4 outColor;"
		"uniform sampler2D texKitten;"
		"void main() {"
		"   outColor = texture(texKitten, Texcoord) * vec4(Color, 1.0);"
		"}";


	// Create and compile the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Create and compile the fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// Link the vertex and fragment shader into a shader program
	this->shaderProgram = glCreateProgram();
	glAttachShader(this->shaderProgram, vertexShader);
	glAttachShader(this->shaderProgram, fragmentShader);
	glBindFragDataLocation(this->shaderProgram, 0, "outColor");
	glLinkProgram(this->shaderProgram);
	glUseProgram(this->shaderProgram);

	printShaderInfoLog(vertexShader);
	printShaderInfoLog(fragmentShader);
	printProgramInfoLog(this->shaderProgram);

	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation(this->shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);

	GLint colAttrib = glGetAttribLocation(this->shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	GLint texAttrib = glGetAttribLocation(this->shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

	this->uniTrans = glGetUniformLocation(this->shaderProgram, "trans");
	glUniformMatrix4fv(this->uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

}

void Sprite::DrawTex()
{

	// Draw a rectangle from the 2 triangles using 6 indices
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void Sprite::DrawTex(mat4 &trans, mat4 &Ortho)
{
	glBindTexture(GL_TEXTURE_2D, this->textures[0]);
	glUseProgram(this->shaderProgram);
	mat4 MVP = Ortho * trans;
	glUniformMatrix4fv(this->uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

	// Draw a rectangle from the 2 triangles using 6 indices
	glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);

	glUniformMatrix4fv(this->uniTrans, 1, GL_FALSE, glm::value_ptr(MVP));

	glBindTexture(GL_TEXTURE_2D, NULL);

}

bool Sprite::LoadVertShader(const char* filePath)
{
		// Shader sources
	const GLchar* vertexSource =
		"#version 330 core\n"
		"in vec2 position;"
		"in vec3 color;"
		"in vec2 texcoord;"
		"uniform mat4 model;"
		"out vec3 Color;"
		"out vec2 Texcoord;"
		"void main() {"
		"   Color = color;"
		"	Texcoord = texcoord;"
		"   gl_Position = model * vec4(position, 0.0, 1.0);"
		"}";
	
	glShaderSource(m_VertexShader, 1, &vertexSource, NULL);
	glCompileShader(m_VertexShader);
	return printShaderInfoLog(m_VertexShader);
}

bool Sprite::LoadFragShader(const char* filePath)
{
		// Shader sources
	const GLchar* fragmentSource =
		"#version 330 core\n"
		"in vec3 Color;"
		"in vec2 Texcoord;"
		"out vec4 outColor;"
		"uniform sampler2D texKitten;"
		"void main() {"
		"   outColor = texture(texKitten, Texcoord) * vec4(Color, 1.0);"
		"}";
	
	glShaderSource(m_FragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(m_FragmentShader);
	return printShaderInfoLog(m_FragmentShader);
}

bool Sprite::LinkShaders()
{
	glAttachShader(shaderProgram, m_FragmentShader);
	glAttachShader(shaderProgram, m_VertexShader);

	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	return printProgramInfoLog(shaderProgram);
}