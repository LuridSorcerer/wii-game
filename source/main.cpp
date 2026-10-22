#include <gccore.h>
#include <wiiuse/wpad.h>
#include <ogc/lwp_watchdog.h>
#include <grrlib.h>

#include "vec2.h"
#include "player.h"
#include "timer.h"
#include "utils.h"

constexpr u32 SOLID_RED      = 0xFF0000FF;
constexpr u32 SOLID_GREEN    = 0x00FF00FF;
constexpr u32 SOLID_BLUE     = 0x0000FFFF;
constexpr u32 SOLID_BLACK    = 0x000000FF;
constexpr u32 SOLID_DARKGRAY = 0x101010FF;
constexpr u32 SOLID_WHITE    = 0xFFFFFFFF;

constexpr float ACCEL    = 500.0f;
constexpr float FRICTION = 1000.0f;
constexpr float MAXSPEED = 200.0f;

static void drawPlayer(Player* p) {
	GRRLIB_Rectangle(
		p->location.x,
		p->location.y,
		p->w,
		p->h,
		SOLID_WHITE,
		true
	);
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
			if (p.velocity.x > fric) {
				p.velocity.x -= fric;
			} else if (p.velocity.x < -fric) {
				p.velocity.x += fric;
			} else {
				p.velocity.x = 0;
			}
		}
		
		if (held & WPAD_BUTTON_DOWN) {
			p.velocity.y += ACCEL * timer.getDeltaTime();
		} else if (held & WPAD_BUTTON_UP) {
			p.velocity.y -= ACCEL * timer.getDeltaTime();
		} else {
			// apply friction
			float fric = FRICTION * timer.getDeltaTime();
			if (p.velocity.y > fric) {
				p.velocity.y -= fric;
			} else if (p.velocity.y < -fric) {
				p.velocity.y += fric;
			} else {
				p.velocity.y = 0;
			}
		}

		// limit player speed
		
		clamp(&p.velocity.x, -MAXSPEED, MAXSPEED);
		clamp(&p.velocity.y, -MAXSPEED, MAXSPEED);

		// move player

		p.location += (p.velocity * timer.getDeltaTime());
		
		clamp(&p.location.x, 0, 640-50);
		clamp(&p.location.y, 0, 480-50);

		// render
		
		GRRLIB_FillScreen(SOLID_DARKGRAY);

		drawPlayer(&p);

        GRRLIB_Render();

	}
	
	GRRLIB_Exit();

	return 0;
}
