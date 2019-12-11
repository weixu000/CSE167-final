#version 330 core

in vec3 vNormal, vPos;
uniform samplerCube cubemap;// cubemap texture sampler

out vec4 fragColor;

void main()
{
    fragColor = texture(cubemap, vPos);
}