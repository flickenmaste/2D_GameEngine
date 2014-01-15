// Will Gilstrap - Game Engine
// 1/15/2013

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <Vector2.h>

static class Entity
{
public:
	vector2 position;
	vector2 speed;
	unsigned int textureID;

	void UpdateEntity();	// Update entities
};

#endif