#include <stdio.h>
#include "proposition.h"

int main(int argc, char *argv[])
{
    Proposition y = proposition_parse("x&(y|z)");


    char buffer[256]={0};
    proposition_format(y,buffer,256);
    printf("%s\n",buffer);

    proposition_delete(y);
    return 0;
}
