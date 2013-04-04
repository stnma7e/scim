#version 120

attribute vec4 position;
attribute vec4 color;

varying vec4 vertColor;

uniform mat4 mvp;

void main()
{
	gl_Position = mvp * position;

	vertColor = color;
}
