#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 128

typedef struct rlst_t {
    char row[MAX_LINE];
    struct rlst_t *next;
} rlst_t;

rlst_t *add_row(rlst_t **gp, char *row) {
    rlst_t *p, *q = (rlst_t *) malloc(sizeof(rlst_t));
    strcpy(q->row, row);
    q->next = NULL;
    
    if (*gp == NULL) {
        *gp = q;
    } else {
        for (p = *gp; p->next != NULL; p = p->next);
        p->next = q;
    }
    
    return q;
}

int score(char **grid, int w, int h, int r, int c) {
    int i, j, ns = 0, ss = 0, es = 0, ws = 0;
    char t = grid[r][c];

    // north
    for (i = r - 1, j = c; i >= 0; i--) {
        ns++;
        if (grid[i][j] >= t) break;
    }
    
    // south
    for (i = r + 1, j = c; i < h; i++) {
        ss++;
        if (grid[i][j] >= t) break;
    }
   
    // east
    for (i = r, j = c + 1; j < w; j++) {
        es++;
        if (grid[i][j] >= t) break;
    }
    
    // west
    for (i = r, j = c - 1; j >= 0; j--) {
        ws++;
        if (grid[i][j] >= t) break;
    }

    // printf("%c (%d) at (%d, %d), s = %d * %d * %d * %d\n",
    //     t, t, r, c, ns, ss, es, ws);

    return ns * ss * es * ws;
}

int main(int argc, char **argv) {
    char s[MAX_LINE], **grid;
    rlst_t *p = NULL, *q;
    int w, h, i, j, m, n;
    
    fgets(s, MAX_LINE, stdin);
    q = add_row(&p, s);
    w = strlen(s) - 1;
    h = 1;
    
    while (fgets(s, MAX_LINE, stdin) != NULL) {
        q = add_row(&q, s);
        h++;
    }
   
    grid = (char **) malloc(sizeof(char *) * h);
    
    for (i = 0; i < h; i++) {
        grid[i] = p->row;
        p = p->next;
    }
    
    m = 0;
    
    for (i = 1; i < h - 1; i++) {
        for (j = 1; j < w - 1; j++) {
            n = score(grid, w, h, i, j);
            if (n > m) m = n;
        }
    }
    
    printf("%d\n", m);
    
    return 0;
}
