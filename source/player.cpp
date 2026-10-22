#include "player.h"

Player::Player() {
    location.x = 100.0f;
    location.y = 100.0f;
    velocity.x = 0.0f;
    velocity.y = 0.0f;
    w = 32;
    h = 48;
}

void Player::update(float deltaTime) {
		// limit player speed
		clamp(&velocity.x, -MAXSPEED, MAXSPEED);
		clamp(&velocity.y, -MAXSPEED, MAXSPEED);

		// move player
	    location += (velocity * deltaTime);
}
