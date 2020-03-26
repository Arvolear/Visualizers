#version 330 core
#extension GL_ARB_gpu_shader_fp64 : enable

in vec2 UV;

uniform double zoom;
uniform double realOffset;
uniform double imagOffset;

uniform int maxIterations;
uniform double maxAbs;

uniform double realBeg;
uniform double realEnd;
uniform double imagBeg;
uniform double imagEnd;

out vec4 color;

double getReal()
{
	return (UV.x * (realEnd - realBeg) + realBeg) / zoom + realOffset;
}

double getImag()
{
	return (UV.y * (imagEnd - imagBeg) + imagBeg) / zoom + imagOffset;
}

double absSq(dvec2 comp)
{
	return comp.x * comp.x + comp.y * comp.y;
}

dvec2 mul(dvec2 left, dvec2 right)
{
	dvec2 res;

	res.x = left.x * right.x - left.y * right.y;
	res.y = left.x * right.y + left.y * right.x;

	return res;
}

dvec2 add(dvec2 left, dvec2 right)
{
	dvec2 res;

	res.x = left.x + right.x;
	res.y = left.y + right.y;

	return res;
}

float compute(dvec2 num)
{
	int iterations = 0;
	dvec2 comp = dvec2(0.0, 0.0);

	while (absSq(comp) <= maxAbs * maxAbs && iterations < maxIterations)
	{
		comp = mul(comp, comp);
		comp = add(comp, num);

		iterations++;
	}	

	return iterations + 1 - log(log2(float(absSq(comp))));
}

vec3 hsv2rgb(vec3 c)
{
	vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
	vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);

	return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

dvec3 findColor()
{
	dvec2 num;

	num.x = getReal();
	num.y = getImag();

	float iter = compute(num);	

	vec3 hsv;

	hsv.x = mod(iter / maxIterations, 0.3f) + 0.5f;
	hsv.y = 0.9f - iter / maxIterations;
	hsv.z = floor(iter) >= maxIterations ? 0.0 : 1.0;

	return dvec3(hsv2rgb(hsv));
}

void main()
{
	color = vec4(findColor(), 1.0);	
}
