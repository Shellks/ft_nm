/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:22:09 by acarlott          #+#    #+#             */
/*   Updated: 2025/01/23 09:34:30 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_nm.h"

void	init_struct(t_nm *nm) {
	nm->files = NULL;
	nm->options = malloc(sizeof(t_options));
	if (nm->options == NULL)
	{
		ft_dprintf(STDERR_FILENO, MEMORY_FAILED);
		exit(EXIT_FAILURE);
	}
	ft_memset(nm->options, 0, sizeof(t_options));
}

int	main(int argc, char **argv) {
	t_nm	nm;

	init_struct(&nm);
	if (args_parser(&nm, argc, argv) == ERROR)
		return (EXIT_FAILURE);
	if (!nm.files) { // add a.out to files if no files is given
		files_handler(&nm, "a.out");
	}
	print_options(&nm);
	print_file_list(&nm);
	files_manager(&nm);
	ft_exit(&nm, EXIT_SUCCESS);
}
