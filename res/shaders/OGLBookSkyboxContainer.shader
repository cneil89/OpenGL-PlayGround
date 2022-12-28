#shader vertex
#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 Position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    Normal = mat3(transpose(inverse(model))) * aNormal;
    Position = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

#shader fragment
#version 450 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform float refractiveIndex;
uniform int reflact;
uniform vec3 cameraPos;
uniform samplerCube skybox;

vec3 GetReflectRefract(int reflact, vec3 I, float RI) {
    if (reflact == 0) {
        return reflect(I, normalize(Normal));
    } else {
        if (reflact == 1) {
            float ratio = 1.00 / RI;
            return refract(I, normalize(Normal), ratio);
        }
    }
}

void main()
{    
    vec3 I = normalize(Position - cameraPos);
    vec3 R = GetReflectRefract(reflact, I, refractiveIndex);
    FragColor = vec4(texture(skybox, R).rgb, 1.0);
}