#include "utils.h"

void clamp(float* f, float min, float max) {
    if (*f < min) {*f = min;}
    if (*f > max) {*f = max;}
}