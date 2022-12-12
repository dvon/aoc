#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 64

typedef struct item_t {
    int w;
    struct item_t *next;
} item_t;

item_t *read_items(char *s) {
    char *p;
    item_t *ip, *items;
    
    ip = items = (item_t *) malloc(sizeof(item_t *));
    ip->w = strtol(&s[17], NULL, 10);
    ip->next = NULL;
   
    for (p = &s[17]; *p != '\n'; p++) {
        if (*p == ',') {
            ip->next = (item_t *) malloc(sizeof(item_t *));
            ip->next->w = strtol(++p, NULL, 10);
            ip->next->next = NULL;
            ip = ip->next;
        }
    }

    return items;
}

typedef struct monkey_t {
    int k, op_by, div_by, t_to, f_to, a;
    char op; // +, *, d (double old), s (square old)
    item_t *items;
    struct monkey_t *next;
} monkey_t;

void add_monkey(monkey_t **mk_lst, int k, item_t *items, char op,
    int op_by, int div_by, int t_to, int f_to) {
    monkey_t *p, *q = (monkey_t *) malloc(sizeof(monkey_t));
    q->k = k;
    q->items = items;
    q->op = op;
    q->op_by = op_by;
    q->div_by = div_by;
    q->t_to = t_to;
    q->f_to = f_to;
    q->a = 0;
    q->next = NULL;
    
    if (*mk_lst == NULL) {
        *mk_lst = q;
    } else {
        for (p = *mk_lst; p->next != NULL; p = p->next);
        p->next = q;
    }
}

int read_monkeys(monkey_t ***monkeys) {
    char s[MAX_LINE], *p;
    item_t *items, *ip;
    int k, op_by, div_by, t_to, f_to, i, n = 0;
    char op;
    monkey_t *mk_lst = NULL, *mp;

    while (fgets(s, MAX_LINE, stdin) != NULL) {
        sscanf(s, "Monkey %d:\n", &k);
        fgets(s, MAX_LINE, stdin);
        items = read_items(s);
        fgets(s, MAX_LINE, stdin);
        op = s[23];
        
        if (s[25] == 'o') {
            if (op == '*') op = 's';
            else if (op == '+') op = 'd';
        } else {
            op_by = strtol(&s[25], NULL, 10);
        }
        
        fgets(s, MAX_LINE, stdin);
        div_by = strtol(&s[21], NULL, 10);
        fgets(s, MAX_LINE, stdin);
        t_to = strtol(&s[29], NULL, 10);
        fgets(s, MAX_LINE, stdin);
        f_to = strtol(&s[30], NULL, 10);
        
        add_monkey(&mk_lst, k, items, op, op_by, div_by,
            t_to, f_to);
        fgets(s, MAX_LINE, stdin);
        n++;
    }
    
    *monkeys = (monkey_t **) malloc(sizeof(monkey_t *) * n);
    
    for (i = 0, mp = mk_lst; i < n; i++, mp = mp->next)
        (*monkeys)[i] = mp;
    
    return n;
}

void throw(monkey_t **monkeys, int from, int to, item_t *item) {
    item_t *p;
    
    // printf("%d from %d to %d\n", item->w, from, to);

    if (monkeys[from]->items == item) {
        monkeys[from]->items = item->next;
    } else {
        for (p = monkeys[from]->items; p->next != item;
            p = p->next);
        p->next = p->next->next;
    }
    
    if (monkeys[to]->items == NULL) {
        monkeys[to]->items = item;
    } else {
        for (p = monkeys[to]->items; p->next != NULL;
            p = p->next);
        p->next = item;
    }
    
    item->next = NULL;
}

int main(int argc, char **argv) {
    monkey_t **monkeys, *mp;
    int n = read_monkeys(&monkeys), i, j, a, b;
    item_t *ip;
    
    for (j = 0; j < 20; j++) {
        for (i = 0; i < n; i++) {
            mp = monkeys[i];
        
            for (ip = mp->items; ip != NULL;
                
                // because throw modifies mp->items ...
                ip = mp->items /* ip = ip->next*/ ) {
                
                // printf("%d %d\n", i, ip->w);
                mp->a++;
                
                if      (mp->op == '+') ip->w += mp->op_by;
                else if (mp->op == '*') ip->w *= mp->op_by;
                else if (mp->op == 'd') ip->w += ip->w;
                else if (mp->op == 's') ip->w *= ip->w;
                
                ip->w /= 3;
                
                if (ip->w % mp->div_by == 0) {
                    throw(monkeys, i, mp->t_to, ip);
                } else {
                    throw(monkeys, i, mp->f_to, ip);
                }
            }
        }
    }
    
    a = b = 0;
    
    for (i = 0; i < n; i++) {
        if (monkeys[i]->a > a) {
            b = a;
            a = monkeys[i]->a;
        } else if (monkeys[i]->a > b) {
            b = monkeys[i]->a;
        }
    }
    
    printf("%d\n", a * b);
    
    return 0;
}
