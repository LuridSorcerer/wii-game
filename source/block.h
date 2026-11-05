#ifndef BLOCK_H
#define BLOCK_H

#include "vec2.h"

class Block {
public:
    vec2 location;
    float w, h;

    Block();
    Block(float x, float y, float w, float h);
    
	float left() const;
	float right() const;
	float top() const;
	float bottom() const;
};

#endif
