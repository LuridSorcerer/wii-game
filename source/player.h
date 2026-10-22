#ifndef PLAYER_H
#define PLAYER_H

#include "vec2.h"

class Player {
public:
	vec2 location, velocity;
	float w, h;
	
	Player();
	void update(float deltaTime);
};

#endif
