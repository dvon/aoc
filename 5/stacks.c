#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 64
#define MAX_STACKS 16

typedef struct stk_t {
    char c;
    struct stk_t *prev;
} stk_t;

void prepend(char c, stk_t **sp) {
    stk_t *s, *t = (stk_t *) malloc(sizeof(stk_t));
    t->c = c;
    t->prev = NULL;
    
    if (*sp == NULL) {
        *sp = t;
    } else {
        for (s = *sp; s->prev != NULL; s = s->prev);
        s->prev = t;
    }
}

void push(char c, stk_t **sp) {
    stk_t *s;

    if (*sp == NULL) {
        prepend(c, sp);
    } else {
        s = (stk_t *) malloc(sizeof(stk_t));
        s->c = c;
        s->prev = *sp;
        *sp = s;
    }
}

char pop(stk_t **sp) {
    char c = (*sp)->c;
    stk_t *s = *sp;
    *sp = (*sp)->prev;
    free(s);
   
    return c;
}

int main(int argc, char **argv) {
    char s[MAX_LINE];
    int i, a, b, c;
    stk_t *st[MAX_STACKS];
    
    for (i = 0; i < MAX_STACKS; i++) st[i] = NULL;
    
    while(fgets(s, MAX_LINE, stdin) != NULL) {
    
        if (s[0] == '[') {
            a = strlen(s) - 1;
            b = 1;
            
            for (i = 1; i < a; i += 4) {
                if (s[i] != ' ') prepend(s[i], &st[b]);
                b++;
            }
        
        } else if (s[0] == 'm') {
            sscanf(s, "move %d from %d to %d\n", &a, &b, &c);
            
            for (i = 0; i < a; i++) {
                push(pop(&st[b]), &st[c]);
            }
        }
    }

    for (i = 1; i < MAX_STACKS; i++) {
        if (st[i] != NULL) printf("%c", pop(&st[i]));
    }
    
    printf("\n");

    return 0;
}
