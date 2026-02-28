#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXTOKEN 100

#define BOOL "bool"
#define CHAR "char"
#define SIGNED "signed"
#define UNSIGNED "unsigned"
#define SHORT "short"
#define INT "int"
#define LONG "long"
#define FLOAT "float"
#define DOUBLE "double"

enum { NAME, PARENS, BRACKETS, PARAMS, DATATYPE };

char *dcl(void);
void dirdcl(char *);
int gettoken(void);
void ungetch(int);
int getch(void);
int str_cmp(const char *, const char *);
int is_datatype();

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
int error;

int main() {
    while (gettoken() != EOF) {
        // Reset
        error = 0;
        datatype[0] = '\0';
        while (tokentype == DATATYPE) {
            strcat(datatype, token);
            gettoken();
        }
        char *out = dcl();
        if (tokentype != '\n') {
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

int is_datatype() {
    if (str_cmp(token, BOOL) == 0 || str_cmp(token, CHAR) == 0 || str_cmp(token, SIGNED) == 0 ||
        str_cmp(token, UNSIGNED) == 0 || str_cmp(token, SHORT) == 0 || str_cmp(token, INT) == 0 ||
        str_cmp(token, LONG) == 0 || str_cmp(token, FLOAT) == 0 || str_cmp(token, DOUBLE) == 0) {
        return 1;
    }
    return 0;
}

int gettoken(void) {
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
            if (tokentype == DATATYPE) {
                *p++ = ' ';
                *p = '\0';
            }
            tokentype = DATATYPE;
            return tokentype;
        }
        return tokentype = NAME;
    } else
        return tokentype = c;
}

char *dcl(void) {
    char *buf = malloc(sizeof(char) * 1000);
    buf[0] = '\0';
    int ns;
    for (ns = 0; tokentype == '*'; ns++) {
        gettoken();
    }
    dirdcl(buf);
    while (ns-- > 0)
        strcat(buf, "pointer to ");
    return buf;
}

void dirdcl(char *s) {
    int type;
    if (tokentype == '(') {
        gettoken();
        strcat(s, dcl());
        if (tokentype != ')') {
            printf("error: missing )\n");
            error = 1;
            return;
        }
    } else if (tokentype == NAME) {
        strcat(s, token);
        strcat(s, ": ");
    } else {
        printf("error: expected name or (dcl)\n");
        error = 1;
        return;
    }
    while (!error && ((type = gettoken()) == '(' || type == BRACKETS))
        if (type == BRACKETS) {
            strcat(s, "array");
            strcat(s, token);
            strcat(s, " of ");
        } else {
            strcat(s, "function ");
            if (gettoken() == DATATYPE) {
                strcat(s, "with params (");
                do {
                    char paramtype[MAXTOKEN];
                    paramtype[0] = '\0';
                    while (tokentype == DATATYPE) {
                        strcat(paramtype, token);
                        gettoken();
                    }
                    strcat(s, dcl());
                    strcat(s, paramtype);
                    if (tokentype == ',') {
                        strcat(s, ", ");
                        gettoken();
                    }
                } while (tokentype == DATATYPE);

                strcat(s, ") ");
            }
            if (tokentype == ')') {
                strcat(s, "returning ");
            }
        }
}


#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}


int str_cmp(const char *s1, const char *s2) {
    for (; *s1 == *s2; s1++, s2++)
        if (*s1 == '\0') {
            return 0;
        }
    return *s1 - *s2;
}
