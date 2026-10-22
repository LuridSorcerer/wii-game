#ifndef PLAYER_H
#define PLAYER_H

#include "vec2.h"
#include "utils.h"

constexpr float MAXSPEED = 200.0f;

class Player {
public:
	vec2 location, velocity;
	float w, h;
	
	Player();
	void update(float deltaTime);
};

#endif
