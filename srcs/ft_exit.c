#include "../include/ft_nm.h"


void ft_exit(t_nm *nm) {
    if (nm->binary != NULL) {
        ft_binary_clear(&nm->binary);
    }
    free(nm->options);
    exit(EXIT_ERROR);
}