#pragma once

#include "Entity.hpp"

class RootEntity : public Entity {
public:
	RootEntity(GameWorld* world) : Entity(world) { }
};



