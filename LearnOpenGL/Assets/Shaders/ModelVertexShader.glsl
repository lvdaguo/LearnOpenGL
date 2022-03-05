#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view_projection;

void main()
{
	gl_Position = view_projection * model * vec4(position, 1.0f);
	TexCoords = texCoords;
}
