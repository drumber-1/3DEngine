#pragma once

#include "Entity.hpp"

class RootEntity : public Entity {
public:
	RootEntity(Engine* engine) : m_engine(engine) {}
};



