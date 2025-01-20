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
# define OPTION_ERROR "Usage: ft_nm [option(s)] [file(s)]\n\
List symbols in [file(s)] (a.out by default).\n\
The options are:\n \
-a, --debug-syms       Display debugger-only symbols\n \
-g, --extern-only      Display only external symbols\n \
-p, --no-sort          Do not sort the symbols\n \
-r, --reverse-sort     Reverse the sense of the sort\n \
-u, --undefined-only   Display only undefined symbols\n\
ft_nm: supported targets: x86_32, x64, object files, .so\n"

// Main struct
typedef struct s_nm
{
    t_options *options;
    t_files  *files;
}	t_nm;

// Main parser function
int args_parser(t_nm *nm, int argc, char **argv);

//Utils function
void ft_exit(t_nm *nm);

#endif