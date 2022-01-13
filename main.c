#include "philosophers.h"

static int errArg(char *str) {
    printf(ERROR " %s\n", str);
    return 1;
}

int main(int argc, char **argv) {
    int *value;

    if (argc < 5 || argc > 6)
        return errArg("argc");
    value = ft_parser(argc, argv);
    if (!value)
        return 1;
    else if (!ft_init(argc, value))
        return 1;
    return 0;
}
