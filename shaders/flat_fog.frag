#version 330 core

in vec3 vPos;
uniform vec3 color;

uniform vec3 eye;

out vec4 fragColor;

vec3 fog(float density, vec3 fogColor, float eyeDistance, vec3 originalColor) {
    float fResult = 1.0 - clamp(exp(-density * eyeDistance), 0.0, 1.0);
    return mix(originalColor, fogColor, fResult);
}

void main()
{
    fragColor = vec4(fog(0.05f, vec3(0.8f, 0.8f, 0.8f), length(eye - vPos), color), 1.0f);
}