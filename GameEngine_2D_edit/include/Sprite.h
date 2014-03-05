// Will Gilstrap - Game Engine
// 2/11/2014

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <SOIL.h>
#include <Entity.h>
#include <tinyxml2.h>
#include <vector>



class Sprite : public Entity
{
public:
	Sprite(void);
	~Sprite(void);
	Sprite( const char* a_pTexture, int a_iWidth, int a_iHeight, vec4 a_v4Color,GLFWwindow* );
	void Draw(mat4 &Ortho);
	void Draw();
	void Input(float a_deltaTime);

	GLint uniTrans;

	void SetVertexData( Vertex* a_vertexData );
	const Vertex* GetVertexData() const;
	//void ViewLookAt(vec4& vCameraPos, vec4& vTargetPos, vec4& up_direction, mat4 * mat);
	std::vector<glm::vec4> animPos;
	std::vector<glm::vec2> animWH;
	void SetUVData(vec2 &a_min, vec2 &a_max, vec2 &scale);
	void SetUVData();
	float animFrames;
	float sheetW, sheetH;
	void SetAnim(const char * filename);
	void Animate(mat4 &Ortho);
	void AnimDraw(mat4 &Ortho);
	void LoadTexture(const char* a_pTexture);

	Vertex m_aoVerts[4];

	vec2 m_minUVCoords;
	vec2 m_maxUVCoords;
	vec2 m_uvScale;
	vec2 m_uvOffset;
	float m_fZoom;

	unsigned int m_uiTexture;
	GLFWwindow * GameWindow;
	//used later
	unsigned int	m_uSourceBlendMode;
	unsigned int	m_uDestinationBlendMode;
	int tex_location;
	int matrix_location;
	int proj_location;
	int view_location;
	vec3 m_v2Scale;
	vec3 m_v3Position;
	mat4 modelMatrix;

protected:

	mat4 viewMatrix;

	vec4 m_v4SpriteColor;

};


inline void	Sprite::SetVertexData( Vertex* a_vertexData )
{
	memcpy( &m_aoVerts, a_vertexData, sizeof(Vertex) * 4 );
}

inline const Vertex* Sprite::GetVertexData() const
{
	return static_cast<const Vertex*>( m_aoVerts );
}

#endif