#include "game.h"

Game::Game() { }

void Game::init() {
    // initialize devices
    GRRLIB_Init();
	WPAD_Init();

    blocks.push_back( Block(200,400,300,10) );
    blocks.push_back( Block(400,200,30,300) );
}

void Game::update() {
    // update delta time
    timer.update();

    // read controller state
    updateControls(p, timer.getDeltaTime());

    // move player
    p.update(timer.getDeltaTime());

    // check for collision
    for ( auto& b : blocks ) {
		if ( isColliding(p,b) ) {
			resolveCollision(p,b);
		}
	}

    // keep player on screen
    clamp(&p.location.x, p.w/2, SCREEN_WIDTH  - (p.w/2));
    clamp(&p.location.y, p.h/2, SCREEN_HEIGHT - (p.h/2));
}

void Game::render() {
    // render
    GRRLIB_FillScreen(SOLID_DARKGRAY);
    renderPlayer(p);
    for (const auto& b : blocks) {
		renderBlock(b);
	}
    GRRLIB_Render();
}

void Game::renderPlayer(const Player& p) {
	float halfwidth  = p.w / 2;
	float halfheight = p.h / 2;
	GRRLIB_Rectangle(
		p.location.x - halfwidth,
		p.location.y - halfheight,
		p.w,
		p.h,
		SOLID_WHITE,
		true
	);
}

void Game::renderBlock(const Block& b) {
	float halfwidth  = b.w / 2;
	float halfheight = b.h / 2;
	GRRLIB_Rectangle(
		b.location.x - halfwidth,
		b.location.y - halfheight,
		b.w,
		b.h,
		SOLID_RED,
		true
	);    
}

void Game::applyFriction(float& velocity, float frictionAmount) {
	if (velocity > frictionAmount) {
		velocity -= frictionAmount;
	} else if (velocity < -frictionAmount) {
		velocity += frictionAmount;
	} else {
		velocity = 0.0f;
	}
}

void Game::updateControls(Player& p, float deltaTime) {
		WPAD_ScanPads();
		//u32 pressed = WPAD_ButtonsDown(0);
		u32 held = WPAD_ButtonsHeld(0);

		float inputX = 0.0f;
		float inputY = 0.0f;

		if (held & WPAD_BUTTON_LEFT ) { inputX -= 1.0f; }
		if (held & WPAD_BUTTON_RIGHT) { inputX += 1.0f; }
		if (held & WPAD_BUTTON_UP   ) { inputY -= 1.0f; }
		if (held & WPAD_BUTTON_DOWN ) { inputY += 1.0f; }

		p.velocity.x += inputX * ACCEL * deltaTime;
		p.velocity.y += inputY * ACCEL * deltaTime;

		if (inputX == 0.0f) { applyFriction(p.velocity.x, FRICTION * deltaTime); }
		if (inputY == 0.0f) { applyFriction(p.velocity.y, FRICTION * deltaTime); }
}

bool Game::isColliding(const Player& p, const Block& b) {
	return p.left()   < b.right()  &&
		   p.right()  > b.left()   &&
		   p.top()    < b.bottom() &&
		   p.bottom() > b.top();
}

void Game::resolveCollision(Player& p, const Block& b) {
    // store the x-axis and y-axis overlap amounts
    float overlapX = 0.0f;
    float overlapY = 0.0f;
    
    // calculate x-axis overlap
	if ( p.left() < b.left() ) {
		overlapX = p.right() - b.left();
	} else { 
		overlapX = p.left() - b.right();
	}
	
	// calculate y-axis overlap
	if ( p.top() < b.top() ) {
		overlapY = p.bottom() - b.top();
	} else {
		overlapY = p.top()  - b.bottom(); 
	}

	// move on the shorter intrusion axis
	if ( abs(overlapX) < abs(overlapY) ) {
		// SYS_Report("overlapX:%f \n",overlapX); 
		p.location.x -= overlapX; 
		p.velocity.x = 0;
	} else {
		// SYS_Report("overlapY:%f \n",overlapY); 
		p.location.y -= overlapY;
		p.velocity.y = 0;
	}
}
