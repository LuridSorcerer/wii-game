#include <gccore.h>
#include <wiiuse/wpad.h>
#include <ogc/lwp_watchdog.h>
#include <grrlib.h>

#include "vec2.h"
#include "player.h"
#include "timer.h"
#include "utils.h"

constexpr u32 SCREEN_WIDTH  = 640;
constexpr u32 SCREEN_HEIGHT = 480;

constexpr u32 SOLID_RED      = 0xFF0000FF;
constexpr u32 SOLID_GREEN    = 0x00FF00FF;
constexpr u32 SOLID_BLUE     = 0x0000FFFF;
constexpr u32 SOLID_BLACK    = 0x000000FF;
constexpr u32 SOLID_DARKGRAY = 0x101010FF;
constexpr u32 SOLID_WHITE    = 0xFFFFFFFF;

constexpr float ACCEL    = 500.0f;
constexpr float FRICTION = 1000.0f;

static void drawPlayer(Player* p) {
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
		false
	);
}

static void applyFriction(float& velocity, float frictionAmount) {
	if (velocity > frictionAmount) {
		velocity -= frictionAmount;
	} else if (velocity < -frictionAmount) {
		velocity += frictionAmount;
	} else {
		velocity = 0.0f;
	}
}

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------

	// initialize variables
	Timer timer;
	Player p;

	// initialize devices
    GRRLIB_Init();
	WPAD_Init();

	// game loop

	while(SYS_MainLoop()) {
		
		// update delta time
		timer.update();

		// read controller state
		WPAD_ScanPads();
		u32 pressed = WPAD_ButtonsDown(0);
		u32 held = WPAD_ButtonsHeld(0);

		// handle controls
		
		if (pressed & WPAD_BUTTON_HOME) {
			break; 
		}

		if (held & WPAD_BUTTON_RIGHT) {
			p.velocity.x += ACCEL * timer.getDeltaTime();
		} else if (held & WPAD_BUTTON_LEFT) {
			p.velocity.x -= ACCEL * timer.getDeltaTime();
		} else {
			// apply friction
			float fric = FRICTION * timer.getDeltaTime();
			applyFriction(p.velocity.x, fric);
		}
		
		if (held & WPAD_BUTTON_DOWN) {
			p.velocity.y += ACCEL * timer.getDeltaTime();
		} else if (held & WPAD_BUTTON_UP) {
			p.velocity.y -= ACCEL * timer.getDeltaTime();
		} else {
			// apply friction
			float fric = FRICTION * timer.getDeltaTime();
			applyFriction(p.velocity.y, fric);
		}

		// move player
		p.update(timer.getDeltaTime());

		// keep player on screen
		clamp(&p.location.x, 0, SCREEN_WIDTH);
		clamp(&p.location.y, 0, SCREEN_HEIGHT);

		// render
		
		GRRLIB_FillScreen(SOLID_DARKGRAY);

		drawPlayer(&p);

        GRRLIB_Render();

	}
	
	GRRLIB_Exit();

	return 0;
}
