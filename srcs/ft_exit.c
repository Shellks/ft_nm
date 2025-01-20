#include "../include/ft_nm.h"


void ft_exit(t_nm *nm) {
    if (nm->files != NULL) {
        lst_files_clear(&nm->files);
    }
    free(nm->options);
    exit(EXIT_ERROR);
}