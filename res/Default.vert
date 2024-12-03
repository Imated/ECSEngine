﻿#version 330 core
layout (location = 0) in vec3 aPos;
layout(location = 1) in vec2 uv;

out vec2 TexCoords;

uniform mat4 mvp;

void main() 
{
    gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    TexCoords = uv;
}
