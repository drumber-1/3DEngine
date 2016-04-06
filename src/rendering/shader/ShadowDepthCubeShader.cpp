#include "ShadowDepthCubeShader.hpp"

ShadowDepthCubeShader::ShadowDepthCubeShader() : Shader("shadow_depth_cube_vert.glsl",
														"shadow_depth_cube_frag.glsl",
														"shadow_depth_cube_geom.glsl") {
	addUniform("modelToWorldMatrix");

	addUniform("projectionMatrices");

	addUniform("test");
	addUniform("tarPlane");
}

void ShadowDepthCubeShader::setCamera(const BaseCameraComponent& camera) {
	setUniform("test", camera.getPosition());
	setUniform("tarPlane", camera.getFarPlane());

	std::vector<glm::mat4> projectionMatrices;
	projectionMatrices.push_back(camera.getViewToProjection() * glm::lookAt(camera.getPosition(), camera.getPosition() + glm::vec3(1.0,0.0,0.0), glm::vec3(0.0,-1.0,0.0)));
	projectionMatrices.push_back(camera.getViewToProjection() * glm::lookAt(camera.getPosition(), camera.getPosition() + glm::vec3(-1.0,0.0,0.0), glm::vec3(0.0,-1.0,0.0)));
	projectionMatrices.push_back(camera.getViewToProjection() * glm::lookAt(camera.getPosition(), camera.getPosition() + glm::vec3(0.0,1.0,0.0), glm::vec3(0.0,0.0,1.0)));
	projectionMatrices.push_back(camera.getViewToProjection() * glm::lookAt(camera.getPosition(), camera.getPosition() + glm::vec3(0.0,-1.0,0.0), glm::vec3(0.0,0.0,-1.0)));
	projectionMatrices.push_back(camera.getViewToProjection() * glm::lookAt(camera.getPosition(), camera.getPosition() + glm::vec3(0.0,0.0,1.0), glm::vec3(0.0,-1.0,0.0)));
	projectionMatrices.push_back(camera.getViewToProjection() * glm::lookAt(camera.getPosition(), camera.getPosition() + glm::vec3(0.0,0.0,-1.0), glm::vec3(0.0,-1.0,0.0)));

	setUniform("projectionMatrices", projectionMatrices);
}

void ShadowDepthCubeShader::draw(const RenderComponent& renderComponent) {
	setUniform("modelToWorldMatrix", renderComponent.getTransformationMatrix());
	renderComponent.mesh->draw();
}