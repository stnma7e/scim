#version 120

attribute vec3 position;
attribute vec3 normal;
attribute vec4 color;
attribute vec2 uv;

varying vec4 vertColor;
varying vec2 texUV;
varying vec3 fragNormal;

uniform mat4 mvp;
uniform mat4 mv;

void main()
{
	gl_Position = mvp * vec4(position, 1.0);

	vertColor = color;
	texUV = uv;
}
