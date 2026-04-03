#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "tokenizer.h"

char *dcl(void);
void dirdcl(char *);

extern int tokentype;
extern char token[MAXTOKEN];
static int error;

void dirdcl(char *s)
{
    int type;
    printf("\tdirdcl(): tokentype: %c\n", tokentype);
    printf("\tdirdcl(): tokentype: %d\n", tokentype);
    printf("\tdirdcl(): token: %s\n\n\n", token);
    if (tokentype == '(') {
        gettoken();
        str_cat(s, dcl());
        if (tokentype != ')') {
            printf("error: missing )\n");
            error = 1;
            return;
        }
    } else if (tokentype == NAME) {
        str_cat(s, token);
        str_cat(s, ": ");
    } else if (tokentype == ',' || tokentype == ')') {
        return;
    } else {
        printf("error: expected name or (dcl)\n");
        error = 1;
        return;
    }
    while (!error && ((type = gettoken()) == '(' || type == BRACKETS))
        if (type == BRACKETS) {
            str_cat(s, "array");
            str_cat(s, token);
            str_cat(s, " of ");
        } else {
            str_cat(s, "function ");
            if (gettoken() == DATATYPE) {
                str_cat(s, "with params (");
                do {
                    char paramtype[MAXTOKEN];
                    paramtype[0] = '\0';
                    while (tokentype == DATATYPE) {
                        str_cat(paramtype, token);
                        gettoken();
                    }
                    str_cat(s, dcl());
                    str_cat(s, paramtype);
                    printf("tokentype: %c\n", tokentype);
                    printf("token: %s\n", token);
                    if (tokentype == ',') {
                        str_cat(s, ", ");
                        gettoken();
                    }
                } while (tokentype == DATATYPE);

                str_cat(s, ") ");
            }
            if (tokentype != ')') {
                error = 1;
            }
            str_cat(s, "returning ");
        }
}

char *dcl(void)
{
    char *buf = malloc(sizeof(char) * 1000);
    buf[0] = '\0';
    int ns;
    for (ns = 0; tokentype == '*'; ns++) {
        gettoken();
    }
    dirdcl(buf);
    while (ns-- > 0)
        str_cat(buf, "pointer to ");
    return buf;
}


int main()
{
    char datatype[MAXTOKEN];
    while (gettoken() != EOF) {
        // Reset
        error = 0;
        datatype[0] = '\0';
        while (tokentype == DATATYPE) {
            str_cat(datatype, token);
            gettoken();
        }
        char *out = dcl();
        if (tokentype != '\n' && tokentype != EOF) {
            printf("syntax error\n");
            error = 1;
        }
        if (!error)
            printf("%s%s\n", out, datatype);
        while (tokentype != '\n' && tokentype != EOF)
            gettoken();
    }
    return 0;
}
