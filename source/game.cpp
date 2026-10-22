#include "game.h"

Game::Game() { }

void Game::init() {
    // initialize devices
    GRRLIB_Init();
	WPAD_Init();

    b.push_back( Block(200,400,300,10) );
}

void Game::update() {
    // update delta time
    timer.update();

    // read controller state
    updateControls(p, timer.getDeltaTime());

    // move player
    p.update(timer.getDeltaTime());

    // check for collision
    isColliding(p,b[0]);

    // keep player on screen
    clamp(&p.location.x, p.w/2, SCREEN_WIDTH  - (p.w/2));
    clamp(&p.location.y, p.h/2, SCREEN_HEIGHT - (p.h/2));
}

void Game::render() {
    // render
    GRRLIB_FillScreen(SOLID_DARKGRAY);
    renderPlayer(&p);
    renderBlock(&b[0]);
    GRRLIB_Render();
}

void Game::renderPlayer(Player* p) {
	float halfwidth  = p->w / 2;
	float halfheight = p->h / 2;
	GRRLIB_Rectangle(
		p->location.x,
		p->location.y,
		1,
		1,
		SOLID_WHITE,
		true
	);
	GRRLIB_Rectangle(
		p->location.x - halfwidth,
		p->location.y - halfheight,
		p->w,
		p->h,
		SOLID_WHITE,
		isColliding(*p,b[0])
	);
}

void Game::renderBlock(Block* b) {
	float halfwidth  = b->w / 2;
	float halfheight = b->h / 2;
	GRRLIB_Rectangle(
		b->location.x - halfwidth,
		b->location.y - halfheight,
		b->w,
		b->h,
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
    float pLeft   = p.location.x - (p.w/2.0f);
    float pRight  = p.location.x + (p.w/2.0f);
    float pTop    = p.location.y - (p.h/2.0f);
    float pBottom = p.location.y + (p.h/2.0f);

    float bLeft   = b.location.x - (b.w/2.0f);
    float bRight  = b.location.x + (b.w/2.0f);
    float bTop    = b.location.y - (b.h/2.0f);
    float bBottom = b.location.y + (b.h/2.0f);

    return pLeft   < bRight  &&
           pRight  > bLeft   &&
           pTop    < bBottom &&
           pBottom > bTop;
}

void Game::resolveCollision(Player& p, const Block& b) {
    
}