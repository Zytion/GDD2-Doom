#version 330

in vec3 Color;

uniform vec3 SolidColor = vec3(-1,-1,-1);
uniform bool Invert = false;
out vec4 Fragment;

void main()
{
	
	vec3 temp = Color;
	
	if(SolidColor.r != -1.0 && SolidColor.g != -1.0 && SolidColor.b != -1.0)
		temp = SolidColor;

	if(Invert == true)
		temp = vec3(1.0f, 1.0f, 1.0f) - temp;
	
	Fragment = vec4(temp, 1);

	return;
}