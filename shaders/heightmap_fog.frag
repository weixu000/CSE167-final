#version 330 core

in vec3 vNormal, vPos;
in float vHeight;

out vec4 fragColor;

uniform sampler2D colormap;
uniform float minHeight, maxHeight;

uniform vec3 eye;

vec3 lightDir = normalize(vec3(-1.0, -1.0, -1.0));

vec3 fog(float density, vec3 fogColor, float eyeDistance, vec3 originalColor) {
    float fResult = 1.0 - clamp(exp(-density * eyeDistance), 0.0, 1.0);
    return mix(originalColor, fogColor, fResult);
}

float cosP(vec3 x, vec3 y){
    return max(0.0f, dot(x, y));
}

void main()
{
    vec3 color = texture(colormap, vec2((vHeight-minHeight)/(maxHeight-minHeight)+0.3f, 0.5)).rgb;
    vec3 N = normalize(vNormal);

    vec3 diffuse = color*(cosP(-lightDir, N)+0.1f);

    fragColor = vec4(fog(0.05f, vec3(0.8f, 0.8f, 0.8f), length(eye - vPos), diffuse), 1.0f);
}