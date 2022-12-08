#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 64

struct dlst_t {
    struct dir_t *dir;
    struct dlst_t *next;
};

struct dir_t {
    int size;
    char name[MAX_LINE];
    struct dir_t *par;
    struct dlst_t *subs;
};

typedef struct dlst_t dlst_t;
typedef struct dir_t dir_t;

dir_t *new_dir(dir_t *par, int size, char *name) {
    dir_t *dir = (dir_t *) malloc(sizeof(dir_t));
    dir->size = size;
    strcpy(dir->name, name);
    dir->par = par;
    dir->subs = NULL;

    return dir;
}

void add_sub(dir_t *dir, int size, char *name) {
    dlst_t *lp, *sub = (dlst_t *) malloc(sizeof(dlst_t));
    sub->dir = new_dir(dir, size, name);
    sub->next = NULL;

    if (dir->subs == NULL) {
        dir->subs = sub;
    } else {
        for (lp = dir->subs; lp->next != NULL; lp = lp->next);
        lp->next = sub;
    }
}

dir_t *root = NULL;

dir_t *cd(dir_t *from, char *to) {
    dlst_t * lp;

    if (strcmp(to, "/") == 0) {
        if (from == NULL) root = new_dir(NULL, 0, "/");
        return root;

    } else if (strcmp(to, "..") == 0) {
        if (from->par == NULL) {
            return from;
        } else {
            return from->par;
        }

    } else if (from->subs != NULL) {
        for (lp = from->subs; lp != NULL; lp = lp->next) {
            if (strcmp(lp->dir->name, to) == 0) {
                return lp->dir;
            }
        }
    }

    return NULL;
}

int del_size = INT_MAX;

int size_search(dir_t *dir, int del_min) {
    dlst_t *lp;
    int size = 0;

    if (dir->subs == NULL) {
        size = dir->size;
    } else {
        for (lp = dir->subs; lp != NULL; lp = lp->next) {
            size += size_search(lp->dir, del_min);
        }
    }
    
    if (del_min > 0 && size >= del_min) {
        if (size < del_size) del_size = size;
    }

    return size;
}

int main(int argc, char **argv) {
    char s[MAX_LINE], t[MAX_LINE];
    int i, m;
    dir_t *d = NULL;

    while (fgets(s, MAX_LINE, stdin) != NULL) {
        for (i = 0; s[i] != '\n' && s[i] != '\0'; i++);
        s[i] = '\0';

        if (s[0] == '$' && s[2] == 'c') {
            d = cd(d, &s[5]);
        
        } else if (s[0] == 'd') {
            add_sub(d, 0, &s[4]);

        } else if (s[0] != '$') {
            sscanf(s, "%d %s\n", &i, t);
            add_sub(d, i, t);
        }
    }

    m = 30000000 - (70000000 - size_search(root, 0));
    size_search(root, m);
    printf("%d\n", del_size);

    return 0;
}
