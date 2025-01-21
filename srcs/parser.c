/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:27:29 by acarlott          #+#    #+#             */
/*   Updated: 2025/01/21 11:19:14 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_nm.h"

static bool	files_handler(t_nm *nm, char *file);
static void options_handler(t_nm *nm, char *option);

// Main parser function
int	args_parser(t_nm *nm, int argc, char **argv)
{
	bool	options_end;

	options_end = false;
	for (int i = 1; i < argc; i++) {
		if (!ft_strcmp(argv[i], "--")) {
			if (options_end) {
				if (files_handler(nm, argv[i]) == false)
					return ERROR;
				continue;
			}
			options_end = true;
			continue;
		}
		if (!options_end && argv[i][0] == '-' && argv[i][1])
			options_handler(nm, argv[i]);
		else
			if (files_handler(nm, argv[i]) == false)
				return ERROR;
	}
	return SUCCESS;
}

// Options parser function
static void options_handler(t_nm *nm, char *option) {
	if (option[1] && option[1] == '-') {
		if (handle_word_option(nm, option) == false) {
			ft_dprintf(STDERR_FILENO, "ft_nm: unrecognized option \'%s\'\n", option);
			handle_options_error(nm);
		}
	} else {
		for (size_t i = 1; i < ft_strlen(option); i++) {
			if (handle_flag_option(nm, option[i]) == false) {
				ft_dprintf(STDERR_FILENO, "ft_nm: unrecognized option \'%c\'\n", option[i]);
				handle_options_error(nm);
			}
		}
	}
}

// Files parser function
static bool files_handler(t_nm *nm, char *file) {
	t_files *node = lst_files_new_node(file);
	if (!node) {
		ft_dprintf(STDERR_FILENO, "Failed to create new list file node..");
		ft_exit(nm, EXIT_ERROR);
	}
	lst_files_add_back(&nm->files, node);
	return true;
}