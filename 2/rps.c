#include <stdio.h>

#define MAX_LINE 64

int main(int argc, char **argv) {
    char s[MAX_LINE];
    int p = 0;

    while (fgets(s, MAX_LINE, stdin) != NULL) {
    
        if ((s[0] == 'A' && s[2] == 'X') ||
            (s[0] == 'B' && s[2] == 'Y') ||
            (s[0] == 'C' && s[2] == 'Z')) {
            
            p += 3;
        
        } else if (
            (s[0] == 'A' && s[2] == 'Y') ||
            (s[0] == 'B' && s[2] == 'Z') ||
            (s[0] == 'C' && s[2] == 'X')) {
            
            p += 6;
        }
        
        p += s[2] - 'W';
    }
    
    printf("%d\n", p);

    return 0;
}
