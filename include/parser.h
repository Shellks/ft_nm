/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:32:18 by acarlott          #+#    #+#             */
/*   Updated: 2025/02/25 18:32:11 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

//boolean
# include <stdbool.h>
// fstat
#include <sys/stat.h>
// ELF struct
#include <elf.h>

typedef struct s_nm t_nm;

// struct containing all possible options
typedef struct s_options
{
    bool a;
    bool g;
    bool p;
    bool r;
    bool u;
}	t_options;


// chained list for files
typedef struct s_files
{
    char *name;
    void *mapped;
    int arch_type;
    off_t   size;
    struct s_files *next;
}	t_files;


// files chained list utils function
t_files	    *lst_files_new_node(char *name);
t_files	    *lst_files_last(t_files *lst);
void	    lst_files_delone(t_files *lst);
void	    lst_files_clear(t_files **lst);
void	    lst_files_add_back(t_files **lst, t_files *new_node);

// args parser Utils
bool handle_flag_option(t_nm *nm, char flag);
bool handle_word_option(t_nm *nm, char *option);
void files_handler(t_nm *nm, char *file);
void handle_options_error(t_nm *nm);
// File parser utils
int get_fd(char *file_name);
off_t get_file_size(int fd);
void *get_mapped_file(int fd, off_t file_size);
bool check_magic_elf_word(void *mapped);
int get_file_arch_type(void *mapped);
void invalid_file(t_nm *nm, t_files *file);
bool check_64bits_file(Elf64_Ehdr *elf_hdr, t_files *file);
bool check_32bits_file(Elf32_Ehdr *elf_hdr, t_files *file);
// DEBUG Function
void print_file_list(t_nm *nm);
void print_options(t_nm *nm);

#endif