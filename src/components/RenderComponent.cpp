#include "RenderComponent.hpp"
#include "../rendering/shader/Shader.hpp"

void RenderComponent::render(Shader& shader) const {
	shader.draw(*this);
}

