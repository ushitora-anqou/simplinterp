#include <ctype.h>
#include <stdio.h>

static char *p;

int parse_integer()
{
    int ival = 0;
    while (isdigit(*p)) {
        ival = ival * 10 + *p - '0';
        p++;
    }
    return ival;
}

int eval()
{
    int ival = parse_integer();
    while (*p++ == '+') {
        ival += parse_integer();
    }

    return ival;
}

int main(int argc, char **argv)
{
    p = argv[1];
    return eval();
}
