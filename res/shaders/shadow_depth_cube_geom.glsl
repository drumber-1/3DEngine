#version 430

layout (triangles) in;
layout (triangle_strip, max_vertices=18) out;

out vec4 fragPositionWorld;

uniform mat4 projectionMatrices[6];

void main() {
	for (int face = 0; face < 6; face++) {
		gl_Layer = face;
		for (int i = 0; i < 3; i++) {
			fragPositionWorld = gl_in[i].gl_Position;
			gl_Position = projectionMatrices[face] * fragPositionWorld;
			EmitVertex();
		}
		EndPrimitive();
	}
}
