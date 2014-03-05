// Will Gilstrap - Game Engine
// 2/11/2014

#include <Engine.h>
#include <Sprite.h>

using namespace tinyxml2;

Sprite::Sprite(void)
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

}


Sprite::~Sprite(void)
{
}
Sprite::Sprite( const char* a_pTexture, int a_iWidth, int a_iHeight, vec4 a_v4Color ,GLFWwindow * window)
{

	GameWindow = window;

	LoadVertShader("exampleVert.glsl");
	LoadFragShader("exampleFrag.glsl");
	LinkShaders();

	m_v4SpriteColor = a_v4Color;

	m_aoVerts[0].Pos = vec3(	-0.5f,  0.5f,  0.0f);
	m_aoVerts[1].Pos = vec3(	0.5f,  0.5f,  0.0f);
	m_aoVerts[2].Pos = vec3(	-0.5f,  -0.5f,  0.0f);
	m_aoVerts[3].Pos = vec3(	0.5f,  -0.5f,  0.0f);

	/*
	m_aoVerts[0].Color = vec4(1.0f,  0.0f,  0.0f, 1.0f);
	m_aoVerts[1].Color = vec4(0.0f,  1.0f,  0.0f, 1.0f);
	m_aoVerts[2].Color = vec4(0.0f,  0.0f,  1.0f, 1.0f);
	m_aoVerts[3].Color = vec4(1.0f,  1.0f,  1.0f, 1.0f);
	*/


	m_aoVerts[0].Color = m_v4SpriteColor;
	m_aoVerts[1].Color = m_v4SpriteColor;
	m_aoVerts[2].Color = m_v4SpriteColor;
	m_aoVerts[3].Color = m_v4SpriteColor;



	m_aoVerts[0].UV = vec2(0.0f,  0.0f);
	m_aoVerts[1].UV = vec2(1.0f,  0.0f);
	m_aoVerts[2].UV = vec2(0.0f,  1.0f);
	m_aoVerts[3].UV = vec2(1.0f,  1.0f);

	GLuint elements[] =
	{
		0,1,2,3
	};

	//Gen Buffers
	glGenBuffers(1,&m_VBO);
	glGenBuffers(1,&m_EBO);
	glGenVertexArrays(1, &m_VAO);

	//Bind Buffers
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	//Put Data into buffers
	glBufferData(GL_ARRAY_BUFFER, 4* sizeof(Vertex), m_aoVerts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	//Enable some attributes
	GLint posAttrib = glGetAttribLocation(m_ShaderProgram,"position");
	glEnableVertexAttribArray(posAttrib);
	GLint colAttrib = glGetAttribLocation(m_ShaderProgram,"color");
	glEnableVertexAttribArray(colAttrib);
	GLint uvAttrib = glGetAttribLocation(m_ShaderProgram,"texcoord");
	glEnableVertexAttribArray(uvAttrib);


	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(7 * sizeof(float)));

	glBindVertexArray(0);
	m_v2Scale = vec3(a_iWidth,a_iHeight,1.0f);
	m_v3Position = vec3(0,0,0);

	//ViewLookAt(vec4(0,0,0,0),vec4(0,0,.5,0),vec4(0,1,0,0), viewMatrix);

	modelMatrix[3][3] = 1.f;
	modelMatrix = glm::scale(modelMatrix, m_v2Scale);
	modelMatrix = glm::translate(modelMatrix,m_v3Position);



	matrix_location = glGetUniformLocation (m_ShaderProgram, "matrix");


	m_uiTexture = 0;
	m_minUVCoords = vec2( 0.f, 0.f );
	m_maxUVCoords = vec2( 1.f, 1.f );
	m_uvScale = vec2( 1.f, 1.f );
	m_uvOffset = vec2( 0.f, 0.f );

	m_uSourceBlendMode	= GL_SRC_ALPHA;
	m_uDestinationBlendMode = GL_ONE_MINUS_SRC_ALPHA;

	// Load textures
	glGenTextures(1, &m_uiTexture);
	glActiveTexture (GL_TEXTURE0);

	int width, height;
	unsigned char* image = SOIL_load_image(a_pTexture, &width, &height, 0, SOIL_LOAD_RGBA);
	glBindTexture( GL_TEXTURE_2D,m_uiTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	tex_location = glGetUniformLocation (m_ShaderProgram, "diffuseTexture");

	proj_location = glGetUniformLocation (m_ShaderProgram, "projection");

	view_location = glGetUniformLocation (m_ShaderProgram, "view");

}

void Sprite::Draw(mat4 &Ortho)
{
	glBindTexture(GL_TEXTURE_2D, m_uiTexture);
	glBlendFunc (m_uSourceBlendMode, m_uDestinationBlendMode);
	glUseProgram(m_ShaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i (tex_location, 0); 

	//modelMatrix = glm::scale(modelMatrix, m_v2Scale);
	modelMatrix = glm::translate(modelMatrix, m_v3Position);

	
	mat4 MVP = Ortho * modelMatrix;

	float dArray[16] = {0.0};

	const float *pSource = (const float*)glm::value_ptr(MVP);
	for (int i = 0; i < 16; ++i)
		dArray[i] = pSource[i];

	//	glUniformMatrix4fv (matrix_location, 1, GL_FALSE, modelMatrix->m_afArray);
	//	glUniformMatrix4fv (view_location, 1, GL_FALSE, viewMatrix->m_afArray);
	//	glUniformMatrix4fv (proj_location, 1, GL_FALSE, Ortho->m_afArray);

	glUniformMatrix4fv (matrix_location, 1, GL_FALSE, glm::value_ptr(MVP));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBindVertexArray(m_VAO);


	glDrawElements(GL_TRIANGLE_STRIP, 4,GL_UNSIGNED_INT,0);
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void Sprite::Draw()
{
	glBlendFunc (m_uSourceBlendMode, m_uDestinationBlendMode);
	glUseProgram(m_ShaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i (tex_location, 0); 

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	//Put Data into buffers
	glBufferData(GL_ARRAY_BUFFER, 4* sizeof(Vertex), m_aoVerts, GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLE_STRIP, 4,GL_UNSIGNED_INT,0);	
}

void Sprite::Input(float a_deltaTime)
{
	if (GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_W))
	{
		modelMatrix = glm::translate(modelMatrix, vec3(0.0f, 0.01f, 0.0f) * a_deltaTime);
	}

	if (GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_A))
	{
		modelMatrix = glm::translate(modelMatrix, vec3(-0.01f, 0.0f, 0.0f) * a_deltaTime);
	}

	if (GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_S))
	{
		modelMatrix = glm::translate(modelMatrix, vec3(0.0f, -0.01f, 0.0f) * a_deltaTime);
	}

	if (GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_D))
	{
		modelMatrix = glm::translate(modelMatrix, vec3(0.01f, 0.0f, 0.0f) * a_deltaTime);
	}

}

void Sprite::SetAnim(const char * filename)
{
	animFrames = 0;
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename);

	tinyxml2::XMLElement * currentNode;
	currentNode = doc.FirstChildElement("TextureAtlas");
	sheetW = currentNode->FloatAttribute("width");
	sheetH = currentNode->FloatAttribute("height");

	currentNode = currentNode->FirstChildElement();

	for(int i = 0; currentNode != NULL; i++)
	{
		float iX0= currentNode->FloatAttribute("x");
		float iY0 = currentNode->FloatAttribute("y");
		float iX1= currentNode->FloatAttribute("width");
		float iY1 = currentNode->FloatAttribute("height");
		glm::vec4 Pos(iX0,iX1,iY0,iY1); // x0, x1, y0, y1 = x, y, z, w
		glm::vec2 WH(iX1 - iX0, iY1 - iY0); // width height

		animPos.push_back(Pos);
		animWH.push_back(WH);

		currentNode = currentNode->NextSiblingElement();
		animFrames++;
	}
}

void Sprite::SetUVData(vec2 &a_min, vec2 &a_max, vec2 &scale)
{
	m_minUVCoords = a_min;
	m_maxUVCoords = a_max;
	m_uvScale = scale;

	m_aoVerts[0].UV = vec2(m_minUVCoords.x/m_uvScale.y, m_minUVCoords.y/m_uvScale.y);
	m_aoVerts[1].UV = vec2(m_minUVCoords.x/m_uvScale.x, m_maxUVCoords.y/m_uvScale.y);
	m_aoVerts[2].UV = vec2(m_maxUVCoords.x/m_uvScale.x, m_minUVCoords.y/m_uvScale.y);
	m_aoVerts[3].UV = vec2(m_maxUVCoords.x/m_uvScale.x, m_maxUVCoords.y/m_uvScale.y);
}

void Sprite::SetUVData()
{
	m_aoVerts[0].UV = vec2(m_minUVCoords.x/m_uvScale.x,m_minUVCoords.y/m_uvScale.y);
	m_aoVerts[1].UV = vec2(m_minUVCoords.x/m_uvScale.x,m_maxUVCoords.y/m_uvScale.y);
	m_aoVerts[2].UV = vec2(m_maxUVCoords.x/m_uvScale.x,m_minUVCoords.y/m_uvScale.y);
	m_aoVerts[3].UV = vec2(m_maxUVCoords.x/m_uvScale.x,m_maxUVCoords.y/m_uvScale.y);
}

void Sprite::Animate(mat4 &Ortho)
{
	for (int i = 0; i < animFrames; i++)
	{
		AnimDraw(Ortho);
		vec2 min(animPos[i].z, animPos[i].x);
		vec2 max(animPos[i].w, animPos[i].y);
		vec2 scale(animWH[i].x, animWH[i].y);
		SetUVData(min, max, scale);
	}
}

void Sprite::AnimDraw(mat4 &Ortho)
{
	glBindTexture(GL_TEXTURE_2D, m_uiTexture);
	glBlendFunc (m_uSourceBlendMode, m_uDestinationBlendMode);
	glUseProgram(m_ShaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i (tex_location, 0); 

	//modelMatrix = glm::scale(modelMatrix, m_v2Scale);
	modelMatrix = glm::translate(modelMatrix, m_v3Position);


	mat4 MVP = Ortho * modelMatrix;

	float dArray[16] = {0.0};

	const float *pSource = (const float*)glm::value_ptr(MVP);
	for (int i = 0; i < 16; ++i)
		dArray[i] = pSource[i];

	//	glUniformMatrix4fv (matrix_location, 1, GL_FALSE, modelMatrix->m_afArray);
	//	glUniformMatrix4fv (view_location, 1, GL_FALSE, viewMatrix->m_afArray);
	//	glUniformMatrix4fv (proj_location, 1, GL_FALSE, Ortho->m_afArray);

	glUniformMatrix4fv (matrix_location, 1, GL_FALSE, glm::value_ptr(MVP));
	
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, 4* sizeof(Vertex), m_aoVerts,GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBindVertexArray(m_VAO);

	glDrawElements(GL_TRIANGLE_STRIP, 4,GL_UNSIGNED_INT,0);
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void Sprite::LoadTexture(const char* a_pTexture)
{
	m_uiTexture = 0;

	m_uSourceBlendMode	= GL_SRC_ALPHA;
	m_uDestinationBlendMode = GL_ONE_MINUS_SRC_ALPHA;

	glGenTextures(1, &m_uiTexture);
	glActiveTexture (GL_TEXTURE0);

	int width, height;
	unsigned char* image = SOIL_load_image(a_pTexture, &width, &height, 0, SOIL_LOAD_RGBA);
	glBindTexture( GL_TEXTURE_2D,m_uiTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	tex_location = glGetUniformLocation (m_ShaderProgram, "diffuseTexture");

	m_minUVCoords = vec2( 0.f, 0.f );
	m_maxUVCoords = vec2( 1.f, 1.f );
	m_uvScale = vec2( 1.f, 1.f );
	m_fZoom = 1.f;
}

vec4 crossVec4(vec4 _v1, vec4 _v2)
{
	vec3 vec1 = vec3(_v1[0], _v1[1], _v1[2]);
	vec3 vec2 = vec3(_v2[0], _v2[1], _v2[2]);
	vec3 res = glm::cross(vec1, vec2);
	return vec4(res[0], res[1], res[2], 1);
}

/*
void ViewLookAt(vec4& vCameraPos, vec4& vTargetPos, vec4& up_direction, vec4 * mat)
{
	vec4 vForward = vTargetPos-vCameraPos;
	vForward = glm::normalize(vForward);

	vec4 vRight = crossVec4(vForward, up_direction);
	vRight = glm::normalize(vRight);

	vec4 vUp = crossVec4(vForward, vRight);

	mat->m_afArray[0] = vRight.x; 
	mat->m_afArray[4] = vRight.y; 
	mat->m_afArray[8] = vRight.z; 
	mat->m_afArray[12] = -(glm::dot(vRight, vCameraPos));   

	mat->m_afArray[1] = vUp.x;
	mat->m_afArray[5] = vUp.y;
	mat->m_afArray[9] = vUp.z;
	mat->m_afArray[13] = -(glm::dot(vUp, vCameraPos));  

	mat->m_afArray[2] = vForward.x; 
	mat->m_afArray[6] = vForward.y; 
	mat->m_afArray[10] = vForward.z; 
	mat->m_afArray[14] = -(glm::dot(vForward, vCameraPos));   

	mat->m_afArray[3] = 0.0f;
	mat->m_afArray[7] = 0.0f;
	mat->m_afArray[11] = 0.0f;
	mat->m_afArray[15] = 1.0f;
}
*/