#include <stdio.h>

int no_matches(int n, char *s) {
    int i;

    if (n == 1) return 1;
    
    for (i = 1; i < n; i++) {
        if (s[0] == s[i]) return 0;
    }
    
    return no_matches(n - 1, ++s);
}

int main(int argc, char **argv) {
    char s[14], t[14], c;
    int k = 0, i;
    
    while ((c = getc(stdin)) != EOF) {
        s[k % 14] = c;
    
        if (k >= 13) {
            for (i = 0; i < 14; i++)
                t[i] = s[(k - (13 - i)) % 14];
            
            if (no_matches(14, t)) {
                printf("%d\n", k + 1);
                break;
            }
        }
        
        k++;
    }

    return 0;
}
