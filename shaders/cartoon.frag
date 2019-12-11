#version 330 core

// input from phong.vert
in vec3 vNormal;
in float vHeight;

uniform sampler2D colormap;
uniform float minHeight, maxHeight;

vec3 lightDir = normalize(vec3(-1.0, -1.0, -1.0));

out vec4 fragColor;

void main()
{
    vec3 L = lightDir;
    vec3 N = normalize(vNormal);

    vec3 objectColor = texture(colormap, vec2((vHeight-minHeight)/(maxHeight-minHeight)+0.3f, 0.5)).rgb;
    float intensity = dot(N, -L) + 0.1;
    vec3 result = intensity * objectColor;
    if (intensity > 0.95){
    }
    else if (intensity > 0.5){
        result =0.8 * result;
    }
    else if (intensity > 0.2){
        result = 0.7 * result;
    }
    else if (intensity > 0.01){
        result = 0.2 * result;
    }
    else {
        result = vec3(0, 0, 0);
    }
    fragColor = vec4(result, 1.0);
}
