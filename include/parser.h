/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:32:18 by acarlott          #+#    #+#             */
/*   Updated: 2025/01/21 09:51:40 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

//boolean
# include <stdbool.h>

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
    struct s_files *next;
}	t_files;


// files chained list utils function
t_files	    *lst_files_new_node(char *name);
t_files	    *lst_files_last(t_files *lst);
void	    lst_files_delone(t_files *lst);
void	    lst_files_clear(t_files **lst);
void	    lst_files_add_back(t_files **lst, t_files *new_node);

// parser Utils
bool handle_flag_option(t_nm *nm, char flag);
bool handle_word_option(t_nm *nm, char *option);
void handle_options_error(t_nm *nm);

// DEBUG Function
void print_file_list(t_nm *nm);
void print_options(t_nm *nm);

#endif