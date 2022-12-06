#include <stdio.h>
#include <string.h>

#define MAX_LINE 64

int main(int argc, char **argv) {
    char s[MAX_LINE], t[MAX_LINE], u[MAX_LINE];
    int sl, tl, ul, i, j, k;
    int p = 0;
    
outer_loop:
    
    while (fgets(s, MAX_LINE, stdin) > 0) {
        sl = strlen(s) - 1;
        fgets(t, MAX_LINE, stdin);
        tl = strlen(t) - 1;
        fgets(u, MAX_LINE, stdin);
        ul = strlen(u) - 1;
        
        for (i = 0; i < sl; i++) {
            for (j = 0; j < tl; j++) {
            
                if (s[i] == t[j]) {
                    for (k = 0; k < ul; k++) {
                    
                        if (s[i] == u[k]) {
                            
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
        }
    }
    
    printf("%d\n", p);
    
    return 0;
}

