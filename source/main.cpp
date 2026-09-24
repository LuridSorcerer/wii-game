#include <gccore.h>
#include <wiiuse/wpad.h>
#include <grrlib.h>

#define SOLID_RED   0xFF0000FF
#define SOLID_GREEN 0x00FF00FF
#define SOLID_BLUE  0x0000FFFF
#define SOLID_BLACK 0x000000FF
#define SOLID_WHITE 0xFFFFFFFF

u32 color = SOLID_BLACK;

struct player {
	float x,y;
};

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------

	player p;
	p.x = 50.0f;
	p.y = 50.0f;

    GRRLIB_Init();

	WPAD_Init();

	while(SYS_MainLoop()) {

		WPAD_ScanPads();

		u32 pressed = WPAD_ButtonsDown(0);
		
		if (pressed & WPAD_BUTTON_HOME) {
			break; 
		}

		u32 held = WPAD_ButtonsHeld(0);

		if (held & WPAD_BUTTON_RIGHT) {
			p.x += 1;
		} else if (held & WPAD_BUTTON_LEFT) {
			p.x -= 1;
		} 
		
		if (held & WPAD_BUTTON_DOWN) {
			p.y += 1;
		} else if (held & WPAD_BUTTON_UP) {
			p.y -= 1;
		} 
		
		GRRLIB_FillScreen(color);
		GRRLIB_Rectangle(p.x,p.y,50,50,SOLID_WHITE,true);

        GRRLIB_Render();		

	}
	
	GRRLIB_Exit();

	return 0;
}
