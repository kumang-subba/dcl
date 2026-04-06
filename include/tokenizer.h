#ifndef TOKENIZER_H
#define TOKENIZER_H

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
#define VOID "void"

enum token_type { NAME, PARENS, BRACKETS, PARAMS, DATATYPE };

int gettoken(void);

#endif
