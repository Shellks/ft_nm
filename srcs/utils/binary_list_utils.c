#include "../../include/ft_nm.h"

t_binary	*ft_binary_new_node(char *name)
{
	t_binary	*new_node;

	new_node = malloc(sizeof(t_binary));
	if (!new_node)
		return (ERROR);
	new_node->name = name;
    new_node->next = NULL;
	return (new_node);
}

t_binary	*ft_binary_last(t_binary *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_binary_delone(t_binary *lst)
{
	if (lst)
		free(lst);
}

void	ft_binary_clear(t_binary **lst)
{
	t_binary	*tmp;

	if (!lst)
		return ;
	while (*lst) {
		tmp = (*lst)->next;
		ft_binary_delone(*lst);
		*lst = tmp;
	}
	*lst = 0;
}

void	ft_binary_add_back(t_binary **lst, t_binary *new_node)
{
	t_binary	*tmp;

	if (!new_node)
		return ;
	if (lst) {
		if (*lst) {
			tmp = ft_binary_last(*lst);
			tmp->next = new_node;
		} else
			*lst = new_node;
	}
}