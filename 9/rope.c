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
    int n, hx = 0, hy = 0, tx = 0, ty = 0, k = 0;
    list_t *loc = NULL;

    while (fgets(s, MAX_LINE, stdin) != NULL) {
        sscanf(s, "%c %d\n", &c, &n);
        
        for (; n > 0; n--) {
        
            if (c == 'R') {
                hx++;
                
                if (hx == tx + 2) {
                    if (hy == ty + 1) ty++;
                    else if (hy == ty - 1) ty--;
                    tx++;
                }
                
            } else if (c == 'L') {
                hx--;
                
                if (hx == tx - 2) {
                    if (hy == ty + 1) ty++;
                    else if (hy == ty - 1) ty--;
                    tx--;
                }
            
            } else if (c == 'U') {
                hy++;
                
                if (hy == ty + 2) {
                    if (hx == tx + 1) tx++;
                    else if (hx == tx - 1) tx--;
                    ty++;
                }
            
            } else if (c == 'D') {
                hy--;
                
                if (hy == ty - 2) {
                    if (hx == tx + 1) tx++;
                    else if (hx == tx - 1) tx--;
                    ty--;
                }
            }
            
            // printf("H: %d,%d  T: %d,%d\n", hx, hy, tx, ty);
            
            k += add_loc(&loc, tx, ty);
        }
    }
    
    printf("%d\n", k);

    return 0;
}
