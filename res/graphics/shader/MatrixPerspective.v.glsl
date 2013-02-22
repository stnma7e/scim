#version 120

attribute vec4 position;
attribute vec4 color;

varying vec4 theColor;

uniform vec2 modelToCamMatx;
uniform mat4 camToClipMatx;

void main()
{
	vec4 cameraPos = position + vec4(modelToCamMatx.x, modelToCamMatx.y, 0.0, 0.0);

	gl_Position = camToClipMatx * cameraPos;
	theColor = color;
}
