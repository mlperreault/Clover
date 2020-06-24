#ifndef COLORS_H_INCLUDED
#define COLORS_H_INCLUDED

struct color_f {
	float r;
	float g;
	float b;
	float a;
};

const color_f RED{ 1,0,0,1 };
const color_f GREEN{ 0,1,0,1 };
const color_f BLUE{ 0,0,1,1 };
const color_f WHITE{ 1,1,1,1 };
const color_f BLACK{ 0,0,0,1 };

#endif
