#version 120

varying vec2 texUV;

struct DirectionalLight
{
	vec3 color;
	float ambientIntensity;
};

uniform sampler2D texUnit;
uniform DirectionalLight d_light;

void main()
{
	gl_FragColor = texture2D(texUnit, texUV) *
		vec4(d_light.color, 1) *
		d_light.ambientIntensity;
}
