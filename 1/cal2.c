#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 64

int main(int argc, char **argv) {
    char s[MAX_LINE];
    int i = 0, a = 0, b = 0, c = 0;
    
    while (fgets(s, MAX_LINE, stdin) != NULL) {
        
        if (s[1]) {
            i += strtol(s, NULL, 10);
        
        } else {
            if (i > a) {
                c = b; b = a; a = i;
            
            } else if (i > b) {
                c = b; b = i;
            
            } else if (i > c) {
                c = i;
            }
            
            i = 0;
        }
    }
    
    printf("%d\n", (a + b + c));
    
    return 0;
}
