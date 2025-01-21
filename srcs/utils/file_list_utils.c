/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:13:06 by acarlott          #+#    #+#             */
/*   Updated: 2025/01/21 09:13:08 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_nm.h"

t_files	*lst_files_new_node(char *name)
{
	t_files	*new_node;

	new_node = malloc(sizeof(t_files));
	if (!new_node)
		return (ERROR);
	new_node->name = name;
    new_node->next = NULL;
	return (new_node);
}

t_files	*lst_files_last(t_files *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lst_files_delone(t_files *lst)
{
	if (lst)
		free(lst);
}

void	lst_files_clear(t_files **lst)
{
	t_files	*tmp;

	if (!lst)
		return ;
	while (*lst) {
		tmp = (*lst)->next;
		lst_files_delone(*lst);
		*lst = tmp;
	}
	*lst = 0;
}

void	lst_files_add_back(t_files **lst, t_files *new_node)
{
	t_files	*tmp;

	if (!new_node)
		return ;
	if (lst) {
		if (*lst) {
			tmp = lst_files_last(*lst);
			tmp->next = new_node;
		} else
			*lst = new_node;
	}
}