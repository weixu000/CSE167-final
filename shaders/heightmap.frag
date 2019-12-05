#version 330 core

in vec3 vNormal;
in float vHeight;

out vec4 fragColor;

uniform sampler2D colormap;
uniform float minHeight, maxHeight;

vec3 lightDir = normalize(vec3(-1.0, -1.0, -1.0));

float cosP(vec3 x, vec3 y){
    return max(0.0f, dot(x, y));
}

void main()
{
    vec3 color = texture(colormap, vec2((vHeight-minHeight)/(maxHeight-minHeight)+0.3f, 0.5)).rgb;
    vec3 N = normalize(vNormal);

    fragColor = vec4(color*(cosP(-lightDir, N)+0.1f), 1.0f);
}