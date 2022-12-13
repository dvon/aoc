/*
 * This version was written using libgmp, with the assumption
 * that REALLY big numbers would be needed for the item values.
 * 
 * To compile and run on a Mac, with libgmp installed via homebrew:
 *
 * $ gcc -o monkeys3 monkeys3.c -lgmp -I/opt/homebrew/include/ -L/opt/homebrew/lib/
 * $ cat input.txt | ./monkeys3
 */

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#define MAX_LINE 64

typedef struct item_t {
    mpz_t w;
    struct item_t *next;
} item_t;

item_t *read_items(char *s) {
    char *cp;
    item_t *items, *ip;

    for (cp = &s[19]; *cp != '\n'; cp++)
        if (*cp == ',') *cp = '\0';
    
    ip = items = (item_t *) malloc(sizeof(item_t));
    mpz_init_set_str(ip->w, &s[18], 10);
    ip->next = NULL;

    for (cp = &s[19]; *cp != '\n'; cp++) {
        if (*cp == '\0') {
            ip->next = (item_t *) malloc(sizeof(item_t));
            mpz_init_set_str(ip->next->w, ++cp, 10);
            ip->next->next = NULL;
            ip = ip->next;
        }
    }

    return items;
}

typedef struct monkey_t {
    item_t *items;
    char op;  // +, *, d (old + old), s (old * old)
    int op_by, div_by, t_to, f_to;
    int a;
    struct monkey_t *next;
} monkey_t;

int read_monkeys(monkey_t ***monkeys) {
    char s[MAX_LINE];
    monkey_t *m = NULL, *p, *q;
    int i, n = 0;

    while (fgets(s, MAX_LINE, stdin) != NULL) {
        n++;
        p = (monkey_t *) malloc(sizeof(monkey_t));
        p->next = NULL;
        p->a = 0;
        
        fgets(s, MAX_LINE, stdin);
        p->items = read_items(s);
        
        fgets(s, MAX_LINE, stdin);
        p->op = s[23];
        p->op_by = strtol(&s[25], NULL, 10);
        if (s[25] == 'o') p->op = (p->op == '+') ? 'd' : 's';

        fgets(s, MAX_LINE, stdin);
        p->div_by = strtol(&s[21], NULL, 10);

        fgets(s, MAX_LINE, stdin);
        p->t_to = strtol(&s[29], NULL, 10);

        fgets(s, MAX_LINE, stdin);
        p->f_to = strtol(&s[30], NULL, 10);

        fgets(s, MAX_LINE, stdin);  // skip blank line

        if (m == NULL) {
            m = p;
        } else {
            for (q = m; q->next != NULL; q = q->next);
            q->next = p;
        }
    }

    *monkeys = (monkey_t **) malloc(sizeof(monkey_t *) * n);
    for (p = m, i = 0; p != NULL; p = p->next, i++) (*monkeys)[i] = p;

    return n;
}

void throw(monkey_t **monkeys, int from, int to, item_t *item) {
    item_t *p;
    
    // mpz_out_str(stdout, 10, item->w);
    // printf(" from %d to %d\n", from, to);

    if (monkeys[from]->items == item) {
        monkeys[from]->items = item->next;
    } else {
        for (p = monkeys[from]->items; p->next != item; p = p->next);
        p->next = p->next->next;
    }
    
    if (monkeys[to]->items == NULL) {
        monkeys[to]->items = item;
    } else {
        for (p = monkeys[to]->items; p->next != NULL; p = p->next);
        p->next = item;
    }
    
    item->next = NULL;
}

int main(int argc, char **argv) {
    char s[MAX_LINE], *cp;
    monkey_t **monkeys, *mp;
    item_t *ip;
    int i, j, k, n = read_monkeys(&monkeys);
    mpz_t r, p;
    mpz_init(r);
    mpz_init_set_si(p, monkeys[0]->div_by);
    
    for (i = 1; i < n; i++)
        mpz_mul_si(p, p, monkeys[i]->div_by);
    
    // mpz_out_str(stdout, 10, p);
    // printf("\n");

    for (j = 0; j < 10000; j++) {
        for (i = 0; i < n; i++) {
            mp = monkeys[i];

            for (ip = mp->items; ip != NULL;    
                // because throw modifies mp->items ...
                ip = mp->items /* ip = ip->next */) {
                
                mp->a++;
                
                if (mp->op == '+')
                    mpz_add_ui(ip->w, ip->w, mp->op_by);
                else if (mp->op == '*')
                    mpz_mul_si(ip->w, ip->w, mp->op_by);
                else if (mp->op == 'd')
                    mpz_add(ip->w, ip->w, ip->w);
                else if (mp->op == 's')
                    mpz_mul(ip->w, ip->w, ip->w);
                
                mpz_mod(ip->w, ip->w, p);
                mpz_mod_ui(r, ip->w, mp->div_by);

                if (mpz_cmp_si(r, 0) == 0) {
                    throw(monkeys, i, mp->t_to, ip);
                } else {
                    throw(monkeys, i, mp->f_to, ip);
                }
            }
        }
        
        if ((j + 1) % 1000 == 0) {
            printf("%d ", j + 1);
            for (i = 0; i < n; i++) printf("%d ", monkeys[i]->a);
            printf("\n");
        }
    }

    j = k = 0;

    for (i = 0; i < n; i++) {
        if (monkeys[i]->a > j) {
            k = j;
            j = monkeys[i]->a;
        } else if (monkeys[i]->a > k) {
            k = monkeys[i]->a;
        }
    }

    printf("%d * %d = %ld\n", j, k, (long) j * k);

    return 0;
}
