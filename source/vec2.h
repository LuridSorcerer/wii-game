#ifndef VEC2_H
#define VEC2_H

struct vec2 {
	float x, y;
	
	vec2 operator*(float f) const {
		return {x*f, y*f};
	}
	
	vec2 operator+(vec2 v) const {
		return { x+v.x, y+v.y };
	}
	
	vec2& operator+=(vec2 v) {
		x += v.x;
		y += v.y;
		return *this;
	}
};

#endif
