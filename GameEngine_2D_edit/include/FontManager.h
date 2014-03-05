#ifndef _FONT_MANAGER_H_
#define _FONT_MANAGER_H_

#include <Sprite.h>
#include <map>


struct Char
{
	union{
		struct{
			std::string sName;
			vec2 v2Size;
			vec4 v4Location;
			float yOffset;
		};
		struct
		{
			std::string Name;
			float width, height;
			float x0,x1,y0,y1;
			float offset;
		};
	};
};

struct Font
{
	vec2 v2Size;
	std::string sSheet;
	float fKerning;
};

class FontManager
{
public:
	FontManager(void);
	~FontManager(void);
	void LoadFont(const char * a_pFontSheet);
	void DrawString(std::string str,vec2 pos,float scale, mat4 &Ortho);
	//private?
	void LoadString(std::string str,vec2 pos,float scale);

	Sprite iSprite;
	Font FontAtlas;
	std::map<char,Char> charMap;
	std::vector<Char> DrawList;
	int CharCount;


	///future use
	GLuint PositionBuffer;
	GLuint ColorBuffer;
	GLuint UVBuffer;
	GLuint MatrixBuffer;


};

#endif // _FONT_MANAGER_H_