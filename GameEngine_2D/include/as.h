// Will Gilstrap - Game Engine
// 1/21/2013

#ifndef __AS_H__
#define __AS_H__

#include <iostream>  // cout
#include <assert.h>  // assert()
#include <string.h>  // strstr()
#include <conio.h>   // kbhit(), getch()
#include <windows.h> // timeGetTime()
#include <angelscript.h>
#include <scriptstdstring.h>
#include <scriptbuilder.h>

using namespace std;

static class as
{
public:
	static int RunApplication(); // Compile and run scripts
};

#endif