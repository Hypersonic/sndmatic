#include <stdio.h>
#include <math.h>
#include <string.h>

#define asint(x) (*(int*)&x)

int clamp(int val, int min, int max) {
    if (val < min) {
        return min;
    }
    if (val > max) {
        return max;
    }
    return val;
}

#define CHANGEAT 0xFFFF
int sound(int input_t) {
    int backing;
    {
        int t = input_t % (3 * CHANGEAT);
        if (t > CHANGEAT) {
            t |= t >> 4;
        }
        if (t > 2 * CHANGEAT) {
            t /= 10;
        }

        backing = (t | t >> (t % 8)) / 100;
        backing |= t | t >> 4;

        backing /= 10;

    }
    int foreground;
    {
        int t = input_t;
        int i;

        foreground = t & t >> 4 - t;

        int potentials[] = {0xCF, 0xC, 0x3F, 0x12, 0x123};
        foreground &= potentials[t/3000 % sizeof(potentials) / sizeof(int)];

    }

    return backing | foreground;
}

int main() {
    long t;
    for (t=0;;t++) {
        putchar(sound(t));
    }
    return 0;
}
