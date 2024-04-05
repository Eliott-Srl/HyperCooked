#include "Utils.h"

int collisions(int x1, int y1, int l1, int h1, int x2, int y2, int l2, int h2) {
    return (x1 < x2 + l2 &&
            x1 + l1 > x2 &&
            y1 < y2 + h2 &&
            y1 + h1 > y2);
}

// https://stackoverflow.com/questions/744766/how-to-compare-ends-of-strings-in-c
int endsWith(const char *str, const char *suffix) {
    if (!str || !suffix) {
        return 0;
    }

    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);

    if (lensuffix > lenstr) {
        return 0;
    }

    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

int startsWith(const char *str, const char *suffix) {
    if (!str || !suffix) {
        return 0;
    }

    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);

    if (lensuffix > lenstr) {
        return 0;
    }

    return strncmp(str, suffix, lensuffix) == 0;
}
