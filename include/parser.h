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

// chained list for binary
typedef struct s_binary
{
    char *name;
    struct s_binary *next;
}	t_binary;


// Binary chained list utils function
t_binary	*ft_binary_new_node(char *name);
t_binary	*ft_binary_last(t_binary *lst);
void	    ft_binary_delone(t_binary *lst);
void	    ft_binary_clear(t_binary **lst);
void	    ft_binary_add_back(t_binary **lst, t_binary *new_node);

// Options chained list utils function
t_options	*ft_options_new_node(char type);
t_options	*ft_options_last(t_options *lst);
void	    ft_options_delone(t_options *lst);
void	    ft_options_clear(t_options **lst);
void	    ft_options_add_back(t_options **lst, t_options *new_node);

#endif