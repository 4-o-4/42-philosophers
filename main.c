#include "./includes/philosophers.h"

int main(int argc, char **argv) {
    int *value;

    if (argc < 5 || argc > 6)
        printf("Error: ...\n");
    else if ((value = ft_parser(argc, argv)))
        printf("...\n");
    return (0);
}
