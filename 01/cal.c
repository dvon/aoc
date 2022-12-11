#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 64

int main(int argc, char **argv) {
    char s[MAX_LINE];
    int i = 0, m = 0;
    
    while (fgets(s, MAX_LINE, stdin) != NULL) {
        
        if (s[1]) {
            i += strtol(s, NULL, 10);
        } else {
            m = (m > i) ? m : i;
            i = 0;
        }
    }
    
    printf("%d\n", m);
    
    return 0;
}
