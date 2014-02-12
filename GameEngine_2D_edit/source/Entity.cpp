#include <Entity.h>

Entity::Entity(void)
{
	//Default Shaders for Default constructor

	const char * VertexShader =	// Vertex Shaders deal with objects in 3D space
		"#version 330\n"
		"layout(location = 0) in vec3 position;"
		"layout(location = 1) in vec4 color;"
		//"in vec2 texcoord;"
		"out vec4 vColor;"
		"void main() {"
		"	vColor = color;"
		"	gl_Position = vec4 (position, 1.0);"
		"}";

	const char * FragmentShader =	// Fragment Shaders dela with pixel data
		"#version 330\n"
		"in vec4 vColor;"
		//"in vec2 texcoord;"
		"out vec4 outColour;"
		"void main () {"
		"	outColour = vColor;"
		"}";
	// Compile Vertex Shader
	m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_VertexShader, 1, &VertexShader, NULL);
	glCompileShader(m_VertexShader);
	printShaderInfoLog(m_VertexShader);

	// Compile Fragment Shader
	m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FragmentShader, 1, &FragmentShader, NULL);
	glCompileShader(m_FragmentShader);
	printShaderInfoLog(m_FragmentShader);

	// Link Shaders into Shader Program
	m_ShaderProgram = glCreateProgram();

	glAttachShader(m_ShaderProgram, m_FragmentShader);
	glAttachShader(m_ShaderProgram, m_VertexShader);

	glLinkProgram(m_ShaderProgram);
	printProgramInfoLog(m_ShaderProgram);

	glUseProgram(m_ShaderProgram);

	// Create VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// Create Buffers
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	GLfloat points[] = 
	{
		-0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f, 1.0,
		0.5f,  0.5f,  0.0f,  0.0f, 0.0f,  1.0f, 1.0,
		-0.5f, -0.5f,  0.0f,  1.0f, 0.0f,  0.0f, 1.0,
		0.5f, -0.5f,  0.0f,  1.0f, 1.0f,  1.0f ,1.0
	};
	glBufferData(GL_ARRAY_BUFFER,sizeof(points),points,	GL_STATIC_DRAW);
	// Specify layout of vertex data
	char *attribute_name = "position";
	GLint posAttrib = glGetAttribLocation(m_ShaderProgram, attribute_name);
	if (posAttrib == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
	}
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 7*(sizeof(float)), 0);

	attribute_name = "color";
	GLint colAttrib = glGetAttribLocation(m_ShaderProgram, attribute_name);
	if (colAttrib == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
	}
	glEnableVertexAttribArray(colAttrib);

	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 7*(sizeof(float)),  (void*)(3 * sizeof(GLfloat)));

	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	GLuint elements[] =
	{
		0,1,2,3
	};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(elements), elements, GL_STATIC_DRAW);

}

Entity::~Entity(void)
{

}

void Entity::Draw()
{
	glUseProgram(m_ShaderProgram);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBindVertexArray(m_VAO);

	glDrawElements(GL_TRIANGLE_STRIP, 6,GL_UNSIGNED_INT,0);	

}
bool Entity::LoadVertShader(const char* filePath)
{
	std::string vs =textFileReader(filePath);
	const char * VertexShader = vs.c_str();
	glShaderSource(m_VertexShader, 1, &VertexShader, NULL);
	glCompileShader(m_VertexShader);
	
	return printShaderInfoLog(m_VertexShader);
}
bool Entity::LoadFragShader(const char* filePath)
{
	std::string vs =textFileReader(filePath);
	const char * FragmentShader = vs.c_str();
	glShaderSource(m_FragmentShader, 1, &FragmentShader, NULL);
	glCompileShader(m_FragmentShader);
	
	return printShaderInfoLog(m_FragmentShader);

}
bool Entity::LinkShaders()
{
	glAttachShader(m_ShaderProgram, m_FragmentShader);
	glAttachShader(m_ShaderProgram, m_VertexShader);

	glLinkProgram(m_ShaderProgram);
	glUseProgram(m_ShaderProgram);
	
	return printProgramInfoLog(m_ShaderProgram);
}