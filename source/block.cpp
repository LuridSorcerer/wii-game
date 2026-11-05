#include "block.h"

Block::Block() { }

Block::Block(float newX, float newY, float newW, float newH) {
    location.x = newX;
    location.y = newY;
    w = newW;
    h = newH;
}

float Block::left()   const { return location.x - (w/2.0f); }

float Block::right()  const { return location.x + (w/2.0f); }

float Block::top()    const { return location.y - (h/2.0f); }

float Block::bottom() const { return location.y + (h/2.0f); }
