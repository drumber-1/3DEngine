#pragma once

class RenderTarget {
public:
	RenderTarget(int width, int height, const BaseCameraComponent* camera) : m_framebuffer(width, height, true),
																			 m_camera(camera) {}
private:
	FrameBuffer m_framebuffer;
	const BaseCameraComponent* m_camera;
};



