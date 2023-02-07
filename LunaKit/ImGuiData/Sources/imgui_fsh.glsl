#version 450 core

layout (location = 0) in vec2 vtxUv;
layout (location = 1) in vec4 vtxColor;

layout (binding = 0) uniform sampler2D tex;

layout (location = 0) out vec4 outColor;

void main() {
    outColor = vtxColor * texture(tex, vtxUv);
}