#version 120

attribute vec3 position;
attribute vec4 color;

varying vec4 vertColor;

uniform mat4 mvp;

void main()
{
	gl_Position = mvp * vec4(position, 1.0);

	vertColor = color;
}
