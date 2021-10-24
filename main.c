#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // isdigit

#define INT_LEN 10

int *freeValue(int *value) {
    free(value);
    return NULL;
}

int *parserValue(const int argc, char **argv) {
    int *value;
    int j;
    int i;

    value = (int *)malloc(sizeof(int) * (argc - 1));
    if (!value)
        return NULL;
    j = 0;
    i = 1;
    while (i && argc > i)
        if ((value[j++] = atoi(argv[i++])) < 0)
            i ^= i;
    if (i)
        return value;
    printf("Error: arg%d - \"%s\"\n", j, argv[j]);
    return freeValue(value);
}

int *parser(const int argc, char **argv) {
    int flag;
    int j;
    int i;

    flag = 1;
    j = 0;
    while (flag && argc > ++j && !(i ^= i))
        while (flag && argv[j][i])
            if (!isdigit(argv[j][i++]) || i > INT_LEN)
                flag ^= flag;
    if (flag)
        return parserValue(argc, argv);
    printf("Error: arg%d - \"%s\"\n", j, argv[j]);
    return NULL;
}

int main(int argc, char **argv) {
    int *value;

    if (argc < 5 || argc > 6)
        printf("Error: ...\n");
    else if ((value = parser(argc, argv)))
        printf("...\n");
    return (0);
}
