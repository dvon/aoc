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

int is_visible(char **grid, int w, int h, int r, int c) {
    int i, j, v = 4;
    char t = grid[r][c];

    // north
    for (i = r - 1, j = c; i >= 0; i--)
        if (grid[i][j] >= t) {
            v--;
            break;
        }
    
    // south
    for (i = r + 1, j = c; i < h; i++)
        if (grid[i][j] >= t) {
            v--;
            break;
        }
    
    // east
    for (i = r, j = c + 1; j < w; j++)
        if (grid[i][j] >= t) {
            v--;
            break;
        }
    
    // west
    for (i = r, j = c - 1; j >= 0; j--)
        if (grid[i][j] >= t) {
            v--;
            break;
        }

    // printf("%c (%d) at (%d, %d), v = %d\n", t, t, r, c, v);

    return v > 0;
}

int main(int argc, char **argv) {
    char s[MAX_LINE], **grid;
    rlst_t *p = NULL, *q;
    int w, h, i, j, v;
    
    fgets(s, MAX_LINE, stdin);
    q = add_row(&p, s);
    w = strlen(s) - 1;
    h = 1;
    
    while (fgets(s, MAX_LINE, stdin) != NULL) {
        q = add_row(&q, s);
        h++;
    }
   
    // printf("%d x %d\n", w, h);
   
    grid = (char **) malloc(sizeof(char *) * h);
    
    for (i = 0; i < h; i++) {
        grid[i] = p->row;
        p = p->next;
    }
    
    v = 0;
    
    for (i = 1; i < h - 1; i++) {
        for (j = 1; j < w - 1; j++) {
            if (is_visible(grid, w, h, i, j)) v++;
            // printf("%c", is_visible(grid, w, h, i, j) ? 'V' : '-');
        }
        // printf("\n");
    }
    
    printf("%d + %d + %d + %d + %d - 4 = %d\n",
        v, w, w, h, h, v + w + w + h + h - 4);
    
    return 0;
}
