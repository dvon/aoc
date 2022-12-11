#include <stdio.h>

#define MAX_LINE 64

void cycle(int *c, int x) {

    if (x - 1 <= *c && *c <= x + 1) {
        printf("#");
    } else {
        printf(".");
    }
    
    if (++(*c) == 40) {
        printf("\n");
        *c = 0;
    }
}

int main(int argc, char **argv) {
    char s[MAX_LINE];
    int c = 0, x = 1, y;
    
    while (fgets(s, MAX_LINE, stdin) != NULL) {
        cycle(&c, x);
        
        if (s[0] == 'a') {
            cycle(&c, x);
            sscanf(s, "addx %d\n", &y);
            x += y;
        }
    }

    return 0;
}
