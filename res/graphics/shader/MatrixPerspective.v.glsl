#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

smooth out vec4 theColor;

uniform vec2 modelToCamMatx;
uniform mat4 camToClipMatx;

void main()
{
	vec4 cameraPos = position + vec4(modelToCamMatx.x, modelToCamMatx.y, 0.0, 0.0);

	gl_Position = camToClipMatx * cameraPos;
	theColor = color;
}
