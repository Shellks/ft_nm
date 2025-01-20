#ifndef FT_NM_H
# define FT_NM_H

#include "parser.h"
#include "../srcs/utils/libft/include/libft.h"

// malloc - free
# include <stdlib.h>

# define EXIT_SUCCESS 0
# define EXIT_ERROR 1
# define SUCCESS 1
# define ERROR 0
# define FALSE 0
# define TRUE 1

// Main struct
typedef struct s_nm
{
    t_options *options;
    t_binary  *binary;
}	t_nm;

// Main parser function
int args_parser(t_nm *nm, int argc, char **argv);

//Utils function
void ft_exit(t_nm *nm);

#endif