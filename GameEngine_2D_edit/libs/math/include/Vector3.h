//class vector 3d
//Last Edit 12/17/2013
//Will Gilstrap
/////////////////////
#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#ifdef DLL
        #define DLLEXPORT __declspec(dllexport)
#else
        #define DLLEXPORT __declspec(dllimport)
#endif

#include <math.h> 
#include <stdlib.h>

class vector3
{
public:
	float x;
	float y;
	float z;

	// operators
	vector3 operator+ (const vector3 &w)
	{
		vector3 temp;
		temp.x = this->x + w.x;
		temp.y = this->y + w.y;
		temp.z = this->z + w.z;
		return temp;
	}

	vector3 operator+= (const vector3 &w)
	{
		vector3 temp;
		temp.x = this->x += w.x;
		temp.y = this->y += w.y;
		temp.z = this->z += w.z;
		return temp;
	}

	vector3 operator+ (float s) //scalar add
	{
		vector3 temp;
		temp.x = this->x + s; 
		temp.y = this->y + s;
		temp.z = this->z + s;
		return temp;
	}

	vector3 operator- (const vector3 &w)
	{
		vector3 temp;
		temp.x = this->x - w.x;
		temp.y = this->y - w.y;
		temp.z = this->z - w.z;
		return temp;
	}

	vector3 operator-= (const vector3 &w)
	{
		vector3 temp;
		temp.x = this->x -= w.x;
		temp.y = this->y -= w.y;
		temp.z = this->z -= w.z;
		return temp;
	}

	vector3 operator- (float s) //scalar sub
	{
		vector3 temp;
		temp.x = this->x - s; 
		temp.y = this->y - s;
		temp.z = this->z - s;
		return temp;
	}

	vector3 operator* (float s) //scalar multi
	{
		vector3 temp;
		temp.x = this->x * s; 
		temp.y = this->y * s;
		temp.z = this->z * s;
		return temp;
	}

	vector3 operator*= (float s) //scalar multi *=
	{
		vector3 temp;
		temp.x = this->x *= s; 
		temp.y = this->y *= s;
		temp.z = this->z *= s;
		return temp;
	}

	vector3 operator/ (float s) //scalar divide
	{
		vector3 temp;
		temp.x = this->x / s; 
		temp.y = this->y / s;
		temp.z = this->z / s;
		return temp;
	}

	vector3 operator/= (float s) //scalar divide /=
	{
		vector3 temp;
		temp.x = this->x /= s; 
		temp.y = this->y /= s;
		temp.z = this->z /= s;
		return temp;
	}
	
	// Magnitude
	static float GetMagnitude(vector3 &v);

	// Normalise
	static vector3 Normalise(vector3 &v);
	
	// Normalise
	static vector3 GetNormal(vector3 &v);
	
	// Dot Product
	static float DotProduct(vector3 &a, vector3 &b);

	// Cross Product
	static vector3 CrossProduct(vector3 &a, vector3 &c);

	// calc angle
	static float GetAngle(vector3 &a, vector3 &b);

	// Linear Interpolation
	static vector3 Lerp(vector3 &a, vector3 &b, float &tX);

};

#endif