#include "vec2.h"

class Block {
public:
    vec2 location;
    float w, h;

    Block();
    Block(float x, float y, float w, float h);
};