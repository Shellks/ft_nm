/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:32:24 by acarlott          #+#    #+#             */
/*   Updated: 2025/02/27 19:02:03 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

#include "parser.h"
#include "../srcs/utils/libft/include/libft.h"

// malloc - free
# include <stdlib.h>
// Open
#include <fcntl.h>
// Errno
#include <errno.h>
// mmap
#include <sys/mman.h>

# define EXIT_SUCCESS 0
# define SUCCESS 1
# define ERROR -1
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
# define MEMORY_FAILED "ft_nm: Failed to allocate memory\n"
# define OPEN_FAILED "ft_nm: Failed to open file \'%s\'\n"

// Main struct
typedef struct s_nm
{
    t_options *options;
    t_files  *files;
}	t_nm;

// Main functions
int  args_parser(t_nm *nm, int argc, char **argv);
void files_manager(t_nm *nm);

// Symbol function
//64bits
char get_64bits_symbol_type(Elf64_Sym *symbol, Elf64_Shdr *section_headers, char *strtab);
void print_64bits_symbols(t_files *file, Elf64_Shdr *section_headers, Elf64_Shdr *symtab_section, Elf64_Shdr *strtab_section, char *shstrtab);
//32bits

// sort method
void sort_symbols_by_name(Elf64_Sym *symbols, int symbol_count, char *strtab);

//Utils function
void ft_exit(t_nm *nm, int error_code);
void ft_perror(char *file);


#endif