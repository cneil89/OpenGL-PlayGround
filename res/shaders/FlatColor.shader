#shader vertex
#version 450 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * aPos;
    ourColor = aColor;
};

#shader fragment
#version 450 core

layout (location = 0) out vec3 aColor;

out vec4 FragColor;

void main()  
{
    FragColor = vec4(aColor, 1.0f);
};
