#include "Utils.h"

int collisions(int x1, int y1, int l1, int h1, int x2, int y2, int l2, int h2) {
    return (x1 < x2 + l2 &&
            x1 + l1 > x2 &&
            y1 < y2 + h2 &&
            y1 + h1 > y2);
}
