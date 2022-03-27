#version 330

attribute vec2 coord2d;

out vec4 pos;
out vec2 complex;

uniform float teta;

vec2 complex_mul(vec2 lhs, vec2 rhs)
{
	return vec2(lhs.x * rhs.x - lhs.y * rhs.y, lhs.x * rhs.y + lhs.y * rhs.x);
}


void main()
{
	complex = complex_mul(vec2(0.7885, 0.0), vec2(cos(teta), sin(teta)));
	// complex = complex_mul(vec2(0.285, 0.01), vec2(cos(teta), sin(teta)));
	//    complex		= complex_mul(vec2(-1.476, 0.0), vec2(cos(teta),
	//    sin(teta)));
	gl_Position = pos = vec4(coord2d, 0.0, 1.0);
}