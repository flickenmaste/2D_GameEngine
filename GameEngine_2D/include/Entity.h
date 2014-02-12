// Will Gilstrap - Game Engine
// 2/11/2014

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <Vector2.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

using glm::mat4;

class Entity
{
public:
	vector2 position;
	vector2 speed;
	unsigned int textureID;

	void UpdateEntity();	// Update entities
};

#endif