#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform sampler2D colormap;
uniform float minHeight, maxHeight;

out vec3 color;// color for this vertex

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    color = texture(colormap, vec2((position.y-minHeight)/(maxHeight-minHeight)+0.1f, 0.5)).rgb;
}