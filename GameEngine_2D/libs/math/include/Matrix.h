//Last Edit 12/11/2013
//Will Gilstrap
/////////////////////
#ifndef _MATRIX_H_
#define _MATRIX_H_

#ifdef DLL
        #define DLLEXPORT __declspec(dllexport)
#else
        #define DLLEXPORT __declspec(dllimport)
#endif

#include <iostream>
#include "ComMath.h"
#include "Vector3.h"
#include "Vector4.h"

class Matrix3
{
public:
	float m_aMatrix[3][3];

	//Constructor
	Matrix3();

	//Set Matrix
	static Matrix3 SetMatrix(vector3 &a, vector3 &b, vector3 &c);

	// matrix multiplication
	static Matrix3 Multi(Matrix3 &a, Matrix3 &b);

	// Create Identity
	static Matrix3 CreateIdentity();

	// Create Rotation
	static Matrix3 CreateRotation(float &angle);

	// Create Translation
	static Matrix3 CreateTranslation(vector3 &v);

	// Get Translation
	static vector3 GetTranslation(Matrix3 &m);

	// Get Rotation
	static float GetRotation(Matrix3 &m);

	// Set Translation
	static Matrix3 Translation(Matrix3 &m, vector3 &v);

	// Set Rotation
	static Matrix3 Rotation(Matrix3 &m, float &angle);

	// Transform Vector
	static vector3 TransformVec(Matrix3 &m, const vector3 &point);

	static vector4 TransformVec(Matrix3 &m, const vector4 &point);

	// Scale
	static vector4 Scale(Matrix3 &m, const vector4 &vec);

	static vector3 Scale(Matrix3 &m, const vector3 &vec);

	// Operators
	Matrix3 operator* (const Matrix3 &w)
	{
		Matrix3 temp;
		float product[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

		for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            // Multiply the row of A by the column of B to get the row, column of product.
            for (int inner = 0; inner < 3; inner++) {
				product[row][col] += this->m_aMatrix[row][inner] * w.m_aMatrix[inner][col];
            }
            //std::cout << product[row][col] << "  ";
        }
        //std::cout << "\n";
		}

		temp.m_aMatrix[0][0] = product[0][0];
		temp.m_aMatrix[0][1] = product[0][1];
		temp.m_aMatrix[0][2] = product[0][2];
		temp.m_aMatrix[1][0] = product[1][0];
		temp.m_aMatrix[1][1] = product[1][1];
		temp.m_aMatrix[1][2] = product[1][2];
		temp.m_aMatrix[2][0] = product[2][0];
		temp.m_aMatrix[2][1] = product[2][1];
		temp.m_aMatrix[2][2] = product[2][2];

		return temp;
	}

};

class Matrix4
{
public:
	float m_aMatrix[4][4];

	//Constructor
	Matrix4();

	//Set Matrix
	static Matrix4 SetMatrix(vector4 &a, vector4 &b, vector4 &c, vector4 &d);

	// matrix multiplication
	static Matrix4 Multi(Matrix4 &a, Matrix4 &b);

	// Create Identity
	static Matrix4 CreateIdentity();

	// Create Rotation Z
	static Matrix4 CreateRotZ(const float &angle);

	// Create Rot X
	static Matrix4 CreateRotX(const float &angle);

	// Create Rot Y
	static Matrix4 CreateRotY(const float &angle);

	// Create Translation
	static Matrix4 CreateTranslation(vector3 &v);

	// Get Translation
	static vector3 GetTranslation(Matrix4 &m);

	// Get Rotation
	static float GetRotation(Matrix4 &m);

	// Set Translation
	static Matrix4 Translation(Matrix4 &m, vector3 &v);

	// Rot Z
	static Matrix4 RotZ(Matrix4 &m, const float &angle);

	// Rot X
	static Matrix4 RotX(Matrix4 &m, const float &angle);

	// Rot Y
	static Matrix4 RotY(Matrix4 &m, const float &angle);

	// Transform point
	static vector4 TransformPoint(Matrix4 &m, const vector4 &point);

	// Transform vector
	static vector3 TransformVec(Matrix4 &m, const vector3 &point);

	// Transform vector
	static vector4 TransformVec(Matrix4 &m, const vector4 &point);

	// Scale
	static vector3 Scale(Matrix4 &m, const vector3 &vec);

	// Scale
	static vector4 Scale(Matrix4 &m, const vector4 &vec);

	// Ortho
	Matrix4 OGLOrthoMatrix(float Left, float Right, float Top, float Bottom, float Far, float Near);

	// Ortho
	Matrix4 OrthoMatrix(float Left, float Right, float Top, float Bottom, float Far, float Near);

	// Operators
	Matrix4 operator* (const Matrix4 &w)
	{
		Matrix4 temp;
		float product[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

		for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            // Multiply the row of A by the column of B to get the row, column of product.
            for (int inner = 0; inner < 4; inner++) {
				product[row][col] += this->m_aMatrix[row][inner] * w.m_aMatrix[inner][col];
            }
            //std::cout << product[row][col] << "  ";
        }
        //std::cout << "\n";
		}

		temp.m_aMatrix[0][0] = product[0][0];
		temp.m_aMatrix[0][1] = product[0][1];
		temp.m_aMatrix[0][2] = product[0][2];
		temp.m_aMatrix[0][3] = product[0][3];
		temp.m_aMatrix[1][0] = product[1][0];
		temp.m_aMatrix[1][1] = product[1][1];
		temp.m_aMatrix[1][2] = product[1][2];
		temp.m_aMatrix[1][3] = product[1][3];
		temp.m_aMatrix[2][0] = product[2][0];
		temp.m_aMatrix[2][1] = product[2][1];
		temp.m_aMatrix[2][2] = product[2][2];
		temp.m_aMatrix[2][3] = product[2][3];
		temp.m_aMatrix[3][0] = product[3][0];
		temp.m_aMatrix[3][1] = product[3][1];
		temp.m_aMatrix[3][2] = product[3][2];
		temp.m_aMatrix[3][3] = product[3][3];

		return temp;
	}

};

#endif