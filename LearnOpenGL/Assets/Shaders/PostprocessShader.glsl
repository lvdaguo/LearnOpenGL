#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

const float offset = 1.0f / 300.0f;

void main()
{   
    // original
    // FragColor = texture(texture1, TexCoords);

    // ����
    // FragColor = vec4(vec3(1.0f - texture(texture1, TexCoords)), 1.0f);
    
    // �Ҷ�
    // FragColor = texture(texture1, TexCoords);
    // float average = 0.2126f * FragColor.r + 0.7152f * FragColor.g + 0.0722f * FragColor.b;
    // FragColor = vec4(average, average, average, 1.0f);

    // ��� ��
    /*
    float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    ); 
    */

    // ��� ģ��
    float kernel[9] = float[](
         1.0 / 16,  2.0 / 16,  1.0 / 16,
         1.0 / 16,  4.0 / 16,  2.0 / 16,
         1.0 / 16,  2.0 / 16,  1.0 / 16
    );

    // ��� ��Ե���
    /*
    float kernel[9] = float[](
         1,  1,  1,
         1, -8,  1,
         1,  1,  1
    );
    */

    vec2 offset[9] = vec2[](
        vec2(-offset,  offset), // ����
        vec2( 0.0f,    offset), // ����
        vec2( offset,  offset), // ����
        vec2(-offset,  0.0f),   // ��
        vec2( 0.0f,    0.0f),   // ��
        vec2( offset,  0.0f),   // ��
        vec2(-offset, -offset), // ����
        vec2( 0.0f,   -offset), // ����
        vec2( offset, -offset)  // ����
    );

    vec3 sampleTex[9];
    for (int i = 0; i < 9; i++) 
    {
        sampleTex[i] = vec3(texture(texture1, TexCoords.st + offset[i]));
    }
    vec3 col = vec3(0.0f);
    for (int i = 0; i < 9; i++)
    {
        col += sampleTex[i] * kernel[i];
    }
    FragColor = vec4(col, 1.0f);
}