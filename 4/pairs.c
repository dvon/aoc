#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 64

int main(int argc, char **argv) {
    char s[MAX_LINE];
    int a, b, c, d, k = 0;

    while(fgets(s, MAX_LINE, stdin) > 0) {
        sscanf(s, "%d-%d,%d-%d\n", &a, &b, &c, &d);
        
        if ((a <= c && b >= d) || (c <= a && d >= b)) k++;
    }
    
    printf("%d\n", k);

    return 0;
}
