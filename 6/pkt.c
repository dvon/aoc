#include <stdio.h>

int main(int argc, char **argv) {
    char s[4], a, b, c, d;
    int k = 0;
    
    while ((d = getc(stdin)) != EOF) {
        s[k % 4] = d;
    
        if (k >= 3) {
            a = s[(k - 3) % 4];
            b = s[(k - 2) % 4];
            c = s[(k - 1) % 4];
            
            if (a != b && a != c && a != d &&
                b != c && b != d && c != d) {
                printf("%c%c%c%c %d\n", a, b, c, d, k + 1);
                break;
            }
        }
        
        k++;
    }

    return 0;
}
