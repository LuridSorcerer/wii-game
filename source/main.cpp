#include <gccore.h>
#include <wiiuse/wpad.h>
#include <grrlib.h>

#include "vec2.h"
#include "player.h"

#define SOLID_RED      0xFF0000FF
#define SOLID_GREEN    0x00FF00FF
#define SOLID_BLUE     0x0000FFFF
#define SOLID_BLACK    0x000000FF
#define SOLID_DARKGRAY 0x101010FF
#define SOLID_WHITE    0xFFFFFFFF

/* TODO: Adjust these when making movement relative to delta time */
#define ACCEL    500.0f
#define FRICTION 1000.0f
#define MAXSPEED 200.0f

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------

	// initialize variables

	Player p;
	p.location.x = 100.0f;
	p.location.y = 100.0f;
	p.velocity.x = 0.0f;
	p.velocity.y = 0.0f;

	float deltaTime = 0.016f; /* TODO: Placeholder */

	// initialize devices
	
    GRRLIB_Init();

	WPAD_Init();

	// game loop

	while(SYS_MainLoop()) {
		
		// TODO: update delta time

		// read controller state

		WPAD_ScanPads();

		u32 pressed = WPAD_ButtonsDown(0);

		u32 held = WPAD_ButtonsHeld(0);

		// handle controls
		
		if (pressed & WPAD_BUTTON_HOME) {
			break; 
		}

		if (held & WPAD_BUTTON_RIGHT) {
			p.velocity.x += ACCEL * deltaTime;
		} else if (held & WPAD_BUTTON_LEFT) {
			p.velocity.x -= ACCEL * deltaTime;
		} else {
			// apply friction
			float fric = FRICTION * deltaTime;
			if (p.velocity.x > fric) {
				p.velocity.x -= fric;
			} else if (p.velocity.x < -fric) {
				p.velocity.x += fric;
			} else {
				p.velocity.x = 0;
			}
		}
		
		if (held & WPAD_BUTTON_DOWN) {
			p.velocity.y += ACCEL * deltaTime;
		} else if (held & WPAD_BUTTON_UP) {
			p.velocity.y -= ACCEL * deltaTime;
		} else {
			// apply friction
			float fric = FRICTION * deltaTime;
			if (p.velocity.y > fric) {
				p.velocity.y -= fric;
			} else if (p.velocity.y < -fric) {
				p.velocity.y += fric;
			} else {
				p.velocity.y = 0;
			}
		}

		// limit player speed
		
		if (p.velocity.x > MAXSPEED) { p.velocity.x = MAXSPEED; }
		if (p.velocity.x < -MAXSPEED) { p.velocity.x = -MAXSPEED; }
		if (p.velocity.y > MAXSPEED) { p.velocity.y = MAXSPEED; }
		if (p.velocity.y < -MAXSPEED) { p.velocity.y = -MAXSPEED; }

		// move player

		p.location += (p.velocity * deltaTime);
		
		// render
		
		GRRLIB_FillScreen(SOLID_DARKGRAY);
		GRRLIB_Rectangle(
			p.location.x,
			p.location.y,
			50,
			50, 
			SOLID_WHITE,
			true
		);

        GRRLIB_Render();		

	}
	
	GRRLIB_Exit();

	return 0;
}
