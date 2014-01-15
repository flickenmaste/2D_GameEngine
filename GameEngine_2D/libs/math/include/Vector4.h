//class vector 4d
//Last Edit 11/19/2013
//Will Gilstrap
/////////////////////
#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#ifdef DLL
        #define DLLEXPORT __declspec(dllexport)
#else
        #define DLLEXPORT __declspec(dllimport)
#endif

#include <math.h> 
#include <stdlib.h>

class vector4
{
public:
	float t;
	float x;
	float y;
	float z;

	static vector4 Normalise(vector4 &v);

	static vector4 Hex(int &val);
};

#endif