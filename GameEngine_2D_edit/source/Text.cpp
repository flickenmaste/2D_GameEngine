// Will Gilstrap - Game Engine
// 2/11/2014

#include <Text.h>


void Text::InitFT(char * filename)
{
	if(!oglText.init(filename, 512, 512))
		return;
}

void Text::DrawFont(char * text)
{
	oglText.beginString();
	oglText.drawString(10, 400, text, 1, 0xFFFFFF80);
	oglText.endString(); // will render the whole at once
}

void Text::parseText()
{
	glm::vec2 UVCoords;
	const char * filename = "SquareFont.fnt";
	tinyxml2::XMLElement * currentElement;
	
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename);
}