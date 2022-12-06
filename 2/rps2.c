#include <stdio.h>

#define MAX_LINE 64

int main(int argc, char **argv) {
    char s[MAX_LINE], c;
    int p = 0;

    while (fgets(s, MAX_LINE, stdin) != NULL) {
    
        if (s[2] == 'X') {
            c = (s[0] == 'A') ? 'Z' : (s[0] == 'B') ? 'X' : 'Y';
        
        } else if (s[2] == 'Y') {
            c = (s[0] == 'A') ? 'X' : (s[0] == 'B') ? 'Y' : 'Z';
        
        } else {
            c = (s[0] == 'A') ? 'Y' : (s[0] == 'B') ? 'Z' : 'X';
        }
    
        p += (s[2] - 'X') * 3 + (c - 'W');
    }
    
    printf("%d\n", p);

    return 0;
}
