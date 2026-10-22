#include "block.h"

Block::Block() { }

Block::Block(float newX, float newY, float newW, float newH) {
    location.x = newX;
    location.y = newY;
    w = newW;
    h = newH;
}