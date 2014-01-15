//class vector 2d
//Last Edit 12/17/2013
//Will Gilstrap
/////////////////////
#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#ifdef DLL
        #define DLLEXPORT __declspec(dllexport)
#else
        #define DLLEXPORT __declspec(dllimport)
#endif

#include <math.h>
#include <stdlib.h>

class vector2
{
public:
	vector2();
	// Gets
	float GetX();
	float GetY();
	// Sets
	void SetX(float nextX);
	void SetY(float nextY);

	vector2 operator+ (const vector2 &w)
	{
		vector2 temp;
		temp.x = this->x + w.x;
		temp.y = this->y + w.y;
		return temp;
	}

	vector2 operator+ (float s) //scalar add
	{
		vector2 temp;
		temp.x = this->x + s; 
		temp.y = this->y + s;
		return temp;
	}

	vector2 operator- (const vector2 &w)
	{
		vector2 temp;
		temp.x = this->x - w.x;
		temp.y = this->y - w.y;
		return temp;
	}

	vector2 operator- (float s) //scalar sub
	{
		vector2 temp;
		temp.x = this->x - s; 
		temp.y = this->y - s;
		return temp;
	}

	vector2 operator* (float s) //scalar multi
	{
		vector2 temp;
		temp.x = this->x * s; 
		temp.y = this->y * s;
		return temp;
	}

	// Dot Product
	static float DotProduct(vector2 &a, vector2 &b);

	// Magnitude
	static float GetMagnitude(vector2 &v);

	// Normalise
	static vector2 GetNormal(vector2 &v);

	// Linear Interpolation
	static vector2 Lerp(vector2 &a, vector2 &b, float &tX);
	
private:
	float x;
	float y;
};

#endif