#include <ctype.h>
#include <stdio.h>

int eval(char *p)
{
    int ival = 0;
    while (isdigit(*p)) {
        ival = ival * 10 + *p - '0';
        p++;
    }

    return ival;
}

int main(int argc, char **argv) { return eval(argv[1]); }
