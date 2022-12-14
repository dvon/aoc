#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

typedef struct list_t {
    char s[MAX_LINE];
    struct list_t *next;
} list_t;

char **MAP;
int W, H, SR, SC, ER, EC, **STEPS;

void walk(int d, int r, int c) {
    STEPS[r][c] = d;
    
    if (r == ER && c == EC) {
        printf("to (%d, %d) in %d steps\n", r, c, d);
        return;
    }
    
    // left
    if (c > 0 && STEPS[r][c - 1] > d + 1 &&
        MAP[r][c - 1] <= MAP[r][c] + 1) {   
        walk(d + 1, r, c - 1);
    }
    
    // right
    if (c < W - 1 && STEPS[r][c + 1] > d + 1 &&
        MAP[r][c + 1] <= MAP[r][c] + 1) {
        walk(d + 1, r, c + 1);
    }
    
    // down
    if (r < H - 1 && STEPS[r + 1][c] > d + 1 &&
        MAP[r + 1][c] <= MAP[r][c] + 1) {
        walk(d + 1, r + 1, c);
    }
    
    // up
    if (r > 0 && STEPS[r - 1][c] > d + 1 &&
        MAP[r - 1][c] <= MAP[r][c] + 1) {
        walk(d + 1, r - 1, c);
    }
}

int main(int argc, char **argv) {
    char s[MAX_LINE], *c;
    list_t *p, *q;
    int i, j;
    
    p = q = (list_t *) malloc(sizeof(list_t));
    fgets(s, MAX_LINE, stdin);
    strcpy(p->s, s);
    W = strlen(s) - 1;
    H = 1;
    
    while (fgets(s, MAX_LINE, stdin) != NULL) {
        H++;
        p->next = (list_t *) malloc(sizeof(list_t));
        strcpy(p->next->s, s);
        p = p->next;
    }
    
   
    MAP = (char **) malloc(sizeof(char *) * H);
    STEPS = (int **) malloc(sizeof(int *) * H);
    
    for (i = 0, p = q; i < H; i++, p = p->next) {
        
        if ((c = strchr(p->s, 'S')) != NULL) {
            SR = i; SC = c - p->s;
        }
        
        if ((c = strchr(p->s, 'E')) != NULL) {
            ER = i; EC = c - p->s;
        }
        
        MAP[i] = p->s;
        STEPS[i] = (int *) malloc(sizeof(int) * W);
        for (j = 0; j < W; j++) STEPS[i][j] = INT_MAX;
    }
   
    MAP[SR][SC] = 'a';
    MAP[ER][EC] = 'z';
    walk(0, SR, SC);
    
    return 0;
}
