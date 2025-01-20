#ifndef PARSER_H
# define PARSER_H

//boolean
# include <stdbool.h>

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


#endif