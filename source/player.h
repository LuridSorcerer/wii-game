#ifndef PLAYER_H
#define PLAYER_H

#include "vec2.h"

class Player {
public:
	vec2 location, velocity;
	
	void update(float deltaTime);
};

#endif
