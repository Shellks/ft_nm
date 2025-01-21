/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:13:00 by acarlott          #+#    #+#             */
/*   Updated: 2025/01/21 10:19:43 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_nm.h"

// Manage short-named options
bool handle_flag_option(t_nm *nm, char flag) {
	bool ret = true;
	if (flag == 'a')
		nm->options->a = true;
	else if (flag == 'g')
		nm->options->g = true;
	else if (flag == 'p')
		nm->options->p = true;
	else if (flag == 'r')
		nm->options->r = true;
	else if (flag == 'u')
		nm->options->u = true;
	else
		ret = false;
	return ret;
}

// Manage long-named options
bool handle_word_option(t_nm *nm, char *option) {
	(void)option;
	bool ret = true;
	if (!ft_strcmp(option, "--debug-syms"))
		nm->options->a = true;
	else if (!ft_strcmp(option, "--extern-only"))
		nm->options->g = true;
	else if (!ft_strcmp(option, "--no-sort"))
		nm->options->p = true;
	else if (!ft_strcmp(option, "--reverse-sort"))
		nm->options->r = true;
	else if (!ft_strcmp(option, "--undefined-only"))
		nm->options->u = true;
	else
		ret = false;
	return ret;
}

// Manage quit and display of error with given option
void handle_options_error(t_nm *nm) {
	ft_dprintf(STDERR_FILENO, OPTION_ERROR);
	ft_exit(nm, EXIT_ERROR);
}

void print_file_list(t_nm *nm) { //DEBUG FUNCTION
	t_files *nm_files = nm->files;
	ft_printf("Files list:\n");
	while (nm_files) {
		ft_printf(" -> %s\n", nm_files->name);
		nm_files = nm_files->next;
	}
}

void print_options(t_nm *nm) { //DEBUG FUNCTION
	ft_printf("Options list:\n");
	if (nm->options->a)
		ft_printf(" -> \'-a\'\n");
	if (nm->options->g)
		ft_printf(" -> \'-g\'\n");
	if (nm->options->p)
		ft_printf(" -> \'-p\'\n");
	if (nm->options->r)
		ft_printf(" -> \'-r\'\n");
	if (nm->options->u)
		ft_printf(" -> \'-u\'\n");
}