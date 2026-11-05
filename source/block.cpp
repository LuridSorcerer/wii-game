#include "block.h"

Block::Block() { }

Block::Block(float newX, float newY, float newW, float newH) {
    location.x = newX;
    location.y = newY;
    w = newW;
    h = newH;
}

const float Block::left()   { return location.x - (w/2.0f); }

const float Block::right()  { return location.x + (w/2.0f); }

const float Block::top()    { return location.y - (h/2.0f); }

const float Block::bottom() { return location.y + (h/2.0f); }
