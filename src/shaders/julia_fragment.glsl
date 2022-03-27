#version 330
#define MAX_ITER 5000

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
	return sqrt(lhs.x * lhs.x + lhs.y * lhs.y);
}

vec2 index_to_complex(vec2 pos)
{
	return vec2(pos.x * 3, pos.y * 3);
}

vec2 julia(vec2 z, vec2 c)
{
	vec2 buff;
	buff = complex_mul(z, z);
	buff = complex_add(buff, c);
	return buff;
}

float mapp(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float map(int x)
{
	return x * 2.0 / MAX_ITER - 1;
}

vec4 get_color(vec2 z, vec2 c)
{
	for (int i = 0; i < MAX_ITER; i++)
	{
		if (complex_module(z) > 4.0)
		{
			float color = mapp(i, 0.0, float(MAX_ITER), 0.1, 1.0);
			return vec4(log(log2(i * 3)), 0.0, 0.0, 1.0);
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