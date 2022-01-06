#shader vertex
#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    ourColor = aColor;
};

#shader fragment
#version 450 core

in vec3 ourColor;

out vec4 FragColor;

void main()  
{
    FragColor = vec4(ourColor.r, ourColor.g, ourColor.b, 1.0f);
};
