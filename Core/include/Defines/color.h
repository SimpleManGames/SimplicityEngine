#ifndef _COLOR_H
#define _COLOR_H

struct Color
{
	Color()
		: red(0)
		, green(0)
		, blue(0)
		, alpha(0)
	{}
	Color(float r, float g, float b, float a = 1.0f)
		: red(r)
		, green(g)
		, blue(b)
		, alpha(a)
	{}
	Color(const Color& c)
		:red(c.red)
		, green(c.green)
		, blue(c.blue)
		, alpha(c.alpha)
	{}

	float red;
	float green;
	float blue;
	float alpha;
};

#endif //_COLOR_H