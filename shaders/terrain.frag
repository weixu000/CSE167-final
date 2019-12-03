#version 330 core

in float height;

out vec4 fragColor;

uniform sampler2D colormap;
uniform float minHeight, maxHeight;

void main()
{
    vec3 color = texture(colormap, vec2((height-minHeight)/(maxHeight-minHeight)+0.3f, 0.5)).rgb;
    fragColor = vec4(color, 1.0f);
}