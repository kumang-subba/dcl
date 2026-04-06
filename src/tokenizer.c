#include <ctype.h>

#include "buffer.h"
#include "common.h"
#include "tokenizer.h"

char token[MAXTOKEN];
int tokentype;


static int is_datatype(void)
{
    if (str_cmp(token, BOOL) == 0 || str_cmp(token, CHAR) == 0 || str_cmp(token, SIGNED) == 0 ||
        str_cmp(token, UNSIGNED) == 0 || str_cmp(token, SHORT) == 0 || str_cmp(token, INT) == 0 ||
        str_cmp(token, LONG) == 0 || str_cmp(token, FLOAT) == 0 || str_cmp(token, DOUBLE) == 0 ||
        str_cmp(token, VOID) == 0) {
        return 1;
    }
    return 0;
}


int gettoken(void)
{
    int c;
    char *p = token;
    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']';)
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch());)
            *p++ = c;
        *p = '\0';
        ungetch(c);
        if (is_datatype()) {
            *p++ = ' ';
            *p = '\0';
            return tokentype = DATATYPE;
        }
        return tokentype = NAME;
    } else
        return tokentype = c;
}
