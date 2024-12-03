#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform float time;

uniform sampler2D ourTexture;
uniform bool useTexture;

void main()
{
    FragColor = vec4(0.922, 0.941, 0.8, 1.0);
    if(useTexture)
        FragColor = texture(ourTexture, TexCoords);
}

//void main()
//{
//    FragColor = vec4(0.922, 0.941, 0.8, 1.0);
//}
