#version 450 core

layout (location = 0) in vec2 inPos;
layout (location = 1) in vec2 inUv;
layout (location = 2) in vec4 inColor;

layout (location = 0) out vec2 vtxUv;
layout (location = 1) out vec4 vtxColor;

layout (std140, binding = 0) uniform VertUBO {
    mat4 proj;
} ubo;

void main() {
    gl_Position = ubo.proj * vec4(inPos, 0.0, 1.0);
    vtxUv       = inUv;
    vtxColor    = inColor;
}
