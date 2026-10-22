#include "game.h"

int main(int argc, char **argv) {

	Game g;
	g.init();

	// game loop
	while(SYS_MainLoop()) {
		g.update();
		g.render();
	}
	
	GRRLIB_Exit();

	return 0;
}
