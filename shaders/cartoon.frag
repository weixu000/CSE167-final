#version 330 core

// input from phong.vert
in vec3 vNormal;
in vec3 vPos;

uniform vec3 eye;

//uniform vec3 lightPos;
//uniform vec3 lightColor;
//uniform float light_linear;

//uniform vec3 objectColor;

vec3 lightPos =vec3(100, 100, 100);
vec3 lightColor=vec3(1.0, 1.0, 1.0);
//float light_linear;

vec3 objectColor = vec3(1.0, 0.0, 0.0);

out vec4 fragColor;

void main()
{
    // Toon Shading parameters
    vec3 L = normalize(lightPos - vPos);
    vec3 N = normalize(vNormal);

    float intensity = dot(N, L);
    vec3 result = intensity * objectColor;
    if (intensity > 0.95){
    }
    else if (intensity > 0.5){
        result = vec3(0.7, 0.7, 0.7) * result;
    }
    else if (intensity > 0.2){
        result = vec3(0.5, 0.5, 0.5) * result;
    }
    //    else if (intensity > 0.08){
    //        result = vec3(0.35, 0.35, 0.35) * result;
    //    }
    else if (intensity > 0.05){
        result = vec3(0.1, 0.1, 0.1) * result;
    }
    else {
        result = vec3(0, 0, 0);
    }
    fragColor = vec4(result, 1.0);
}
