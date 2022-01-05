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

in vec3 ourColor;

out vec4 FragColor;

void main()  
{
    FragColor = vec4(ourColor, 1.0f);
};
