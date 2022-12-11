#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 64

typedef struct list_t {
    int x, y;
    struct list_t *next;
} list_t;

int add_loc(list_t **loc, int x, int y) {
    list_t *lp;
    
    if (*loc == NULL) {
        *loc = (list_t *) malloc(sizeof(list_t));
        (*loc)->x = x;
        (*loc)->y = y;
        (*loc)->next = NULL;
    } else {
        for (lp = *loc; lp->next != NULL; lp = lp->next)
            if (lp->x == x && lp->y == y) return 0;
        
        if (lp->x == x && lp->y == y) return 0;
        
        lp->next = (list_t *) malloc(sizeof(list_t));
        lp->next->x = x;
        lp->next->y = y;
        lp->next->next = NULL;
        lp = lp->next;
    }
    
    return 1;
}

int main(int argc, char **argv) {
    char c, s[MAX_LINE];
    int i, n, k = 0, x[10], y[10];
    list_t *loc = NULL;
    
    for (i = 0; i < 10; i++) {
        x[i] = 0;
        y[i] = 0;
    }

    while (fgets(s, MAX_LINE, stdin) != NULL) {
        sscanf(s, "%c %d\n", &c, &n);
        
        for (; n > 0; n--) {
        
            if (c == 'R') {
                x[0]++;
            } else if (c == 'L') {
                x[0]--;
            } else if (c == 'U') {
                y[0]++;
            } else if (c == 'D') {
                y[0]--;
            }
            
            for (i = 1; i < 10; i++) {
            
                if (x[i - 1] == x[i]) {
                    if (y[i - 1] == y[i] + 2) y[i]++;
                    else if (y[i - 1] == y[i] - 2) y[i]--;
                
                } else if (y[i - 1] == y[i]) {
                    if (x[i - 1] == x[i] + 2) x[i]++;
                    else if (x[i - 1] == x[i] - 2) x[i]--;
                
                } else if (
                    (x[i - 1] == x[i] + 1 && y[i - 1] == y[i] + 2) ||
                    (x[i - 1] == x[i] + 2 && y[i - 1] == y[i] + 2) ||
                    (x[i - 1] == x[i] + 2 && y[i - 1] == y[i] + 1)) {
                    x[i]++;
                    y[i]++;

                } else if (
                    (x[i - 1] == x[i] - 1 && y[i - 1] == y[i] + 2) ||
                    (x[i - 1] == x[i] - 2 && y[i - 1] == y[i] + 2) ||
                    (x[i - 1] == x[i] - 2 && y[i - 1] == y[i] + 1)) {
                    x[i]--;
                    y[i]++;
                
                } else if (
                    (x[i - 1] == x[i] + 1 && y[i - 1] == y[i] - 2) ||
                    (x[i - 1] == x[i] + 2 && y[i - 1] == y[i] - 2) ||
                    (x[i - 1] == x[i] + 2 && y[i - 1] == y[i] - 1)) {
                    x[i]++;
                    y[i]--;
                
                } else if (
                    (x[i - 1] == x[i] - 1 && y[i - 1] == y[i] - 2) ||
                    (x[i - 1] == x[i] - 2 && y[i - 1] == y[i] - 2) ||
                    (x[i - 1] == x[i] - 2 && y[i - 1] == y[i] - 1)) {
                    x[i]--;
                    y[i]--;
                }
            }
            
            // printf("%d,%d\n", x[9], y[9]);
            k += add_loc(&loc, x[9], y[9]);
        }
    }
    
    // for (; loc != NULL; loc = loc->next)
    //     printf("%d,%d\n", loc->x, loc->y);
    
    printf("%d\n", k);

    return 0;
}
