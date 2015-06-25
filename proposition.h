#ifndef PROPOSITION_H
#define PROPOSITION_H
#include <stdlib.h>

typedef void *Proposition;

Proposition proposition_new(void);//creates an empty proposition
void proposition_delete(Proposition);//also deletes children!

Proposition proposition_set_value(Proposition,char);//for now all props are 1 char
Proposition proposition_set_left(Proposition,Proposition);
Proposition proposition_set_right(Proposition,Proposition);

char proposition_get_value(const Proposition);
Proposition proposition_get_left(const Proposition);
Proposition proposition_get_right(const Proposition);

int proposition_print(const Proposition, char *,size_t);//buffer & size

#endif // PROPOSITION_H
