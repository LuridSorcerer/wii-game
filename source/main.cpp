#include <gccore.h>
#include <wiiuse/wpad.h>
#include <grrlib.h>

#define SOLID_RED   0xFF0000FF
#define SOLID_GREEN 0x00FF00FF
#define SOLID_BLUE  0x0000FFFF
#define SOLID_BLACK 0x000000FF
#define SOLID_WHITE 0xFFFFFFFF

int color = SOLID_BLACK;

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------

    GRRLIB_Init();

	WPAD_Init();

	while(SYS_MainLoop()) {

		WPAD_ScanPads();

		u32 pressed = WPAD_ButtonsDown(0);
		
		if (pressed & WPAD_BUTTON_HOME) {
			break; 
		}

		if (pressed & WPAD_BUTTON_UP) {
			color = SOLID_RED;
		} else if (pressed & WPAD_BUTTON_DOWN) {
			color = SOLID_GREEN;
		} else if (pressed & WPAD_BUTTON_LEFT) {
			color = SOLID_BLUE;
		} else if (pressed & WPAD_BUTTON_RIGHT) {
			color = SOLID_WHITE;
		}
		
		GRRLIB_FillScreen(color);

        GRRLIB_Render();		

	}
	
	GRRLIB_Exit();

	return 0;
}
