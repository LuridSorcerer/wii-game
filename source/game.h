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

class Game {

public: 
	Timer timer;
	Player p;

    Game();
    void init();
    void update();
    void render();
    void renderPlayer(Player*);
    void applyFriction(float&,float);
    void updateControls(Player&,float);
};