// Will Gilstrap - Game Engine
// 1/22/2013

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <Vector2.h>
#include <Matrix.h>

class Entity
{
public:
	vector2 position;
	vector2 speed;
	unsigned int textureID;

	void UpdateEntity();	// Update entities
};

#endif