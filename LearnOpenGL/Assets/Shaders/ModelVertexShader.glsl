#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 TexCoords;
out vec3 ourPos;

uniform mat4 model;
uniform mat4 ViewProjection;

void main()
{
	gl_Position = ViewProjection * model * vec4(position, 1.0f);
	// ourPos = vec3(gl_Position);
	TexCoords = texCoords;
}
