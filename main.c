#include <stdio.h>
#include "proposition.h"

int main(int argc, char *argv[])
{
    Proposition y = proposition_new();
    proposition_set_value(y,'y');

    Proposition x = proposition_new();
    proposition_set_value(x,'x');

    Proposition and = proposition_new();
    proposition_set_value(and,'&');
    proposition_set_left(and,x);
    proposition_set_right(and,y);


    char buffer[256]={0};
    proposition_print(and,buffer,256);
    printf("%s",buffer);

    proposition_delete(and);
    return 0;
}
