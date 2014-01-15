//Last Edit 11/19/2013
//Will Gilstrap
/////////////////////
#ifndef _COMMATH_H_
#define _COMMATH_H_
#define FPI 3.14159265358979323846

#ifdef DLL
        #define DLLEXPORT __declspec(dllexport)
#else
        #define DLLEXPORT __declspec(dllimport)
#endif

#include <math.h>
#include <stdlib.h>


class Math
{
public:
	// convert degree to radian
	static float ToRadian(float a_degree);

	// convert radian to degree
	static float ToDegree(float a_radian);

	// Shift to next power of 2
	static unsigned int NextPowerOf2(unsigned int n);
};

#endif