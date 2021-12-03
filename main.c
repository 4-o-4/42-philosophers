#include "./includes/philosophers.h"

int main(int argc, char **argv) {
    int *value;

    if (argc < 5 || argc > 6)
        return ft_error("...");
    value = ft_parser(argc, argv);
    if (!value)
        return 1;
    else if (!ft_ww(argc, value))
        return 1;
    return 0;
}
