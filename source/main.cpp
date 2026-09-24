#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

#include <grrlib.h>

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------

    GRRLIB_Init();

	while(SYS_MainLoop()) {

        GRRLIB_FillScreen(0xFF0000FF);
        GRRLIB_Render();		

	}

	return 0;
}
