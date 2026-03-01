# DCL

A C declaration parser that converts C declarations into readable English.

## Example:

Input:

```c
int (*fp)(int n, char *s)
```

Output:

```bash
fp: pointer to function taking (n: int, s: pointer to char) retunring int
```

## Usage:

```bash
$ dcl <<< "char **argv"
argv: pointer to pointer to char
```

## Todo

- [ ] Check if data type provided is valid
- [ ] Add support for type qualifier
- [ ] Support function parameter without names
