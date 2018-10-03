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

int parse_add()
{
    int ival = parse_integer();
    while (*p != '\0') {
        switch (*p) {
            case '+':
                p++;
                ival += parse_integer();
                break;
            case '-':
                p++;
                ival -= parse_integer();
                break;
            default:
                goto end;
        }
    }
end:
    return ival;
}

int eval()
{
    return parse_add();
    /*
    int ival = parse_integer();
    while (*p != '\0') {
        switch (*p++) {
            case '+':
                ival += parse_integer();
                break;
            case '-':
                ival -= parse_integer();
                break;
            case '*':
                ival *= parse_integer();
                break;
            case '/':
                ival /= parse_integer();
                break;
        }
    }

    return ival;
    */
}

int main(int argc, char **argv)
{
    p = argv[1];
    return eval();
}
