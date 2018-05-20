#ifndef COLOR_H
#define COLOR_H

#include "3DMath\3DMath.h"

struct Color
{
	Color():
		r(0),
		g(0),
		b(0) {}

	Color(float R, float G, float B):
		r(R / 255.0f),
		g(G / 255.0f),
		b(B / 255.0f) {}

	Color(int HEX):
		r((HEX & 0xff0000) >> 16),
		g((HEX & 0x00ff00) >> 8),
		b((HEX & 0x0000ff)) {};
	math::Vector3 ToVector3() const { return math::Vector3(r, g, b); }

	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Black;
	static const Color White;


	float r;
	float g;
	float b;
};

#endif //!COLOR_H
