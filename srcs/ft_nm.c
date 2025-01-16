#include "../include/ft_nm.h"

void init_struct(t_nm *nm) {
    nm->binary = NULL;
    nm->options = malloc(sizeof(t_options));
    if (nm->options == NULL) {
        ft_printf("Failed to allocate memory for struct options\n");
        exit(EXIT_ERROR);
    }
    ft_memset(nm->options, 0, sizeof(t_options));
}

int main(int argc, char **argv) {
    t_nm    nm;

    if (argc == 1) {
        ft_printf("ft_nm: 'a.out': No such file\n");
        return ERROR;
    }
    init_struct(&nm);
    if (args_parser(&nm, argc, argv) == -1)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}