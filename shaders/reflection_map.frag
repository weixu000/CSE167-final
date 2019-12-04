#version 330 core

// input from phong.vert
in vec3 vNormal, vPos;

uniform vec3 eye;
uniform samplerCube cubemap;// cubemap texture sampler

out vec4 fragColor;

void main()
{
    vec3 N = normalize(vNormal);
    vec3 V = normalize(eye - vPos);
    vec3 L = reflect(-V, N);

    fragColor = texture(cubemap, L);
}