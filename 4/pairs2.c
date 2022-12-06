#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 64

int main(int argc, char **argv) {
    char s[MAX_LINE];
    int a, b, c, d, k = 0;

    while(fgets(s, MAX_LINE, stdin) != NULL) {
        sscanf(s, "%d-%d,%d-%d\n", &a, &b, &c, &d);
        
        if (!(c > b || a > d)) k++;
    }
    
    printf("%d\n", k);

    return 0;
}
