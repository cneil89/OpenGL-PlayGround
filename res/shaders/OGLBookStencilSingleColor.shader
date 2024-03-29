#shader vertex
#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;    
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
}


#shader fragment
#version 450 core

out vec4 FragColor;

void main()
{
    FragColor = vec4(0.15, 0.75, 0.15, 1.0);
}