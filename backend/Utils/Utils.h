#ifndef HYPERCOOKED_UTILS_H
#define HYPERCOOKED_UTILS_H

#include "../backend.h"

int collisionsBtRectangles(int x1, int y1, int l1, int h1, int x2, int y2, int l2, int h2);
int collisionsBtCircles(int x1, int y1, int r1, int x2, int y2, int r2);
int collisionsBtRectanglesAndCircles(int x1, int y1, int l1, int h1, int x2, int y2, int r2);
int endsWith(const char *str, const char *suffix);
int startsWith(const char *str, const char *suffix);

#endif //HYPERCOOKED_UTILS_H
