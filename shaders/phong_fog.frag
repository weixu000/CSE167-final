#version 330 core

in vec3 vNormal, vPos;

uniform vec3 ks, kd, ka;
uniform float alpha;

vec3 lightPos =vec3(100, 100, 100);
vec3 lightColor=vec3(1.0, 1.0, 1.0);

uniform vec3 eye;

vec3 fog(float density, vec3 fogColor, float eyeDistance, vec3 originalColor) {
    float fResult = 1.0 - clamp(exp(-density * eyeDistance), 0.0, 1.0);
    return mix(originalColor, fogColor, fResult);
}

void main() {
    vec3 L = normalize(lightPos - vPos);
    vec3 N = normalize(vNormal);
    vec3 V = normalize(eye - vPos);
    vec3 R = 2 * dot(L, N) * N - L;

    vec3 lc = lightColor;
    vec3 phongColor = lc*vec3(ka + kd * cosP(L, N)+ ks * pow(cosP(R, V), alpha));

    fragColor = vec4(fog(0.05f, vec3(0.8f, 0.8f, 0.8f), length(eye - vPos), phongColor), 1.0f);
}
