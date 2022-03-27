#version 330
#define MAX_ITER 10
#define SCALE	 1.7

out vec4 FragColor;
in vec4	 pos;
in vec2	 complex;


vec2 complex_add(vec2 lhs, vec2 rhs)
{
	return vec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

vec2 complex_mul(vec2 lhs, vec2 rhs)
{
	return vec2(lhs.x * rhs.x - lhs.y * rhs.y, lhs.x * rhs.y + lhs.y * rhs.x);
}

float complex_module(vec2 lhs)
{
	// return inversesqrt(lhs.x * lhs.x + lhs.y * lhs.y);
	return sqrt(lhs.x * lhs.x + lhs.y * lhs.y);
}

vec2 index_to_complex(vec2 pos)
{
	return vec2(pos.x * SCALE, pos.y * SCALE);
}

vec2 julia(vec2 z, vec2 c)
{
	vec2 buff;
	buff = complex_mul(z, z);
	buff = complex_add(buff, c);
	return buff;
}

float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

vec4 get_color(vec2 z, vec2 c)
{
	for (int i = 0; i < MAX_ITER; i++)
	{
		if (complex_module(z) > 2.0)
		{
			float color = mapf(i, 0.0, MAX_ITER, 0.1, 0.9);
			float red	= 1.0 * ((1 + cos(6.28 * color)) / 2);
			float green = 1.0 * ((1 + cos(15.5488 * color)) / 2);
			float blue	= 1.0 * ((1 + cos(2.5 * color)) / 2);
			return vec4(red, green, blue, 1.0);
		}
		z = julia(z, c);
	}
	return vec4(0.0, 0.0, 0.0, 0.0); // MAX ITER REACHED
}

void main()
{
	// float color_ = get_color(index_to_complex(pos.xy), complex);
	// FragColor	 = vec4(color_, color_ * 0.33, 0.0, 1.0);
	FragColor = get_color(index_to_complex(pos.xy), complex);
	//   gl_FragColor = vec4(1.0, 0.0, 0.0, 0.1);
}