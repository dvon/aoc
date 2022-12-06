#include <stdio.h>
#include <string.h>

#define MAX_LINE 64

int main(int argc, char **argv) {
    char s[MAX_LINE];
    int i, j, n, p = 0;

outer_loop:
    
    while (fgets(s, MAX_LINE, stdin) != NULL) {
        n = strlen(s) - 1;
        
        for (i = 0; i < n / 2; i++) {
            for (j = n / 2; j < n; j++) {
                if (s[i] == s[j]) {
                    
                    if (s[i] <= 'Z') {
                        p += s[i] - 'A' + 27;
                    } else {
                        p += s[i] - 'a' + 1;
                    }
                    
                    goto outer_loop;
                }
            }
        }
    }

    printf("%d\n", p);

    return 0;
}
