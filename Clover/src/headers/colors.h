#ifndef COLORS_H_INCLUDED
#define COLORS_H_INCLUDED

template<typename T>
struct color{
	T r;
	T g;
	T b;
	T a;
};

const color<float> RED{ 1.0f, 0.0f, 0.0f, 1.0f };
const color<float> GREEN{ 0.0f, 1.0f, 0.0f, 1.0f };
const color<float> BLUE{ 0.0f, 0.0f, 1.0f, 1.0f };
const color<float> WHITE{ 1.0f, 1.0f, 1.0f, 1.0f };
const color<float> BLACK{ 0.0f, 0.0f, 0.0f, 1.0f };

#endif
