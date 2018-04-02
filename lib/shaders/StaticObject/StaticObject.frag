#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec2 inTexCoord;

layout(location = 0) out vec4 outColor;

void main()
{
  outColor = vec4(inTexCoord.x, inTexCoord.y, 1.0, 1.0);
}
