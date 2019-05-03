#version 330

uniform vec4 cin;
uniform vec2 a;
uniform sampler2D tttt;
out vec4 color;

void main()
{
	if (abs(a.x - 1) < 0.01)
		color = texture(tttt, vec2(0.3, 0.3));
	else
		color = cin;
}