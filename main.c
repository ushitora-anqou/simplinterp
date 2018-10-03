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

int parse_mul()
{
    int ival = parse_integer();
    while (*p != '\0') {
        switch (*p) {
            case '*':
                p++;
                ival *= parse_integer();
                continue;
            case '/':
                p++;
                ival /= parse_integer();
                continue;
        }
        break;
    }
    return ival;
}

int parse_add()
{
    int ival = parse_mul();
    while (*p != '\0') {
        switch (*p) {
            case '+':
                p++;
                ival += parse_mul();
                continue;
            case '-':
                p++;
                ival -= parse_mul();
                continue;
        }
        break;
    }
    return ival;
}

int eval() { return parse_add(); }

int main(int argc, char **argv)
{
    p = argv[1];
    return eval();
}
