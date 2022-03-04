#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourPos;

uniform sampler2D texture_diffuse1;

void main()
{    
    // FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    // FragColor = vec4(TexCoords, 1.0f, 1.0f);
    FragColor = texture(texture_diffuse1, TexCoords);
}