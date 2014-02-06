// Will Gilstrap - Game Engine
// 2/4/2014

#ifndef __TEXT_H__
#define __TEXT_H__

#include <OpenGLText.h>
#include <XML2.h>
#include <stdio.h>
#include <fstream>
#include <glm.hpp>


class Text
{
public:
	OpenGLText oglText;
	void InitFT(char * filename);
	void DrawFont(char * text);

	void parseText();
};

#endif