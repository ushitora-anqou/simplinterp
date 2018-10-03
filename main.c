#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static char *p;
static char *funcbuf[256];

_Noreturn void error(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

void expect(char ch)
{
    if (*p++ != ch) error("unexpected char");
}

int parse_add();
int parse_exprs();

int parse_integer()
{
    int ival = 0;
    while (isdigit(*p)) {
        ival = ival * 10 + *p - '0';
        p++;
    }
    return ival;
}

int parse_funccall()
{
    if (*p == 'P') {
        p++;
        expect('(');
        int ival = parse_add();
        expect(')');
        printf("%d\n", ival);
        return 0;
    }

    if ('A' <= *p && *p <= 'Z') {
        int name = *p;
        p++;
        expect('(');
        expect(')');
        char *old_p = p;
        p = funcbuf[name];
        int ival = parse_exprs();
        p = old_p;
        return ival;
    }

    return parse_integer();
}

int parse_mul()
{
    int ival = parse_funccall();
    while (*p != '\0') {
        switch (*p) {
            case '*':
                p++;
                ival *= parse_funccall();
                continue;
            case '/':
                p++;
                ival /= parse_funccall();
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

void parse_funcdef()
{
    int n = *p++;
    expect('{');
    funcbuf[n] = p;
    while (*p != '\0' && *p++ != '}')
        ;
}

int parse_exprs()
{
    int ival = parse_add();
    while (*p == ';') {
        p++;
        ival = parse_add();
    }
    return ival;
}

int eval()
{
    while (1) {
        if ('A' <= *p && *p <= 'Z' && *(p + 1) == '{') {
            parse_funcdef();
            continue;
        }

        return parse_exprs();
    }
}

int main(int argc, char **argv)
{
    p = argv[1];
    return eval();
}
