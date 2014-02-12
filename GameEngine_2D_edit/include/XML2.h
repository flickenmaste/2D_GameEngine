// Will Gilstrap - Game Engine
// 2/11/2014

#ifndef __XML2_H__
#define __XML2_H__

#include <iostream>
#include <tinyxml2.h>


static class tiny2
{
public:
	static void parseDoc(const char * filename);
	void parseText(const char * filename);
};

#endif