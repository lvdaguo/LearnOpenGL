#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

const float offset = 1.0f / 300.0f;

void main()
{   
    // original
    // FragColor = texture(texture1, TexCoords);

    // 反相
    // FragColor = vec4(vec3(1.0f - texture(texture1, TexCoords)), 1.0f);
    
    // 灰度
    // FragColor = texture(texture1, TexCoords);
    // float average = 0.2126f * FragColor.r + 0.7152f * FragColor.g + 0.0722f * FragColor.b;
    // FragColor = vec4(average, average, average, 1.0f);

    // 卷积 锐化
    /*
    float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    ); 
    */

    // 卷积 模糊
    float kernel[9] = float[](
         1.0 / 16,  2.0 / 16,  1.0 / 16,
         1.0 / 16,  4.0 / 16,  2.0 / 16,
         1.0 / 16,  2.0 / 16,  1.0 / 16
    );

    // 卷积 边缘检测
    /*
    float kernel[9] = float[](
         1,  1,  1,
         1, -8,  1,
         1,  1,  1
    );
    */

    vec2 offset[9] = vec2[](
        vec2(-offset,  offset), // 左上
        vec2( 0.0f,    offset), // 正上
        vec2( offset,  offset), // 右上
        vec2(-offset,  0.0f),   // 左
        vec2( 0.0f,    0.0f),   // 中
        vec2( offset,  0.0f),   // 右
        vec2(-offset, -offset), // 左下
        vec2( 0.0f,   -offset), // 正下
        vec2( offset, -offset)  // 右下
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