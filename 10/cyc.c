#include <stdio.h>

#define MAX_LINE 64

int main(int argc, char **argv) {
    char s[MAX_LINE];
    int c = 0, x = 1, k = 0, y;
    
    while (fgets(s, MAX_LINE, stdin) != NULL) {
        // printf("%s", s);
        // printf("  x = %d\n", x);

        c++;

        if ((c - 20) % 40 == 0) {
            // printf("  %d = %d * %d\n", c * x, c, x);
            k += c * x;
        }
        
        if (s[0] == 'a') {
            c++;
        
            if ((c - 20) % 40 == 0) {
                // printf("  %d = %d * %d\n", c * x, c, x);
                k += c * x;
            }
        
            sscanf(s, "addx %d\n", &y);
            x += y;
        }
        
        if (c >= 220) break;
    }
    
    printf("%d\n", k);

    return 0;
}
