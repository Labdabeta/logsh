#include <stdio.h>
#include "proposition.h"

int main(int argc, char *argv[])
{
    Proposition p = 
        proposition_set_left(
                proposition_set_right(
                    proposition_make('&'),
                    proposition_make('c')),
                proposition_set_left(
                    proposition_set_right(
                        proposition_make('|'),
                        proposition_make('b')),
                    proposition_set_right(
                        proposition_make('!'),
                        proposition_make('a'))));



    char buffer[256]={0};
    proposition_format(p,buffer,256);
    printf("%s\n",buffer);

    proposition_delete(p);
    return 0;
}
