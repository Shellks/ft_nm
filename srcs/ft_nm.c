/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:22:09 by acarlott          #+#    #+#             */
/*   Updated: 2025/01/22 14:53:42 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_nm.h"

void	init_struct(t_nm *nm) {
	nm->files = NULL;
	nm->options = malloc(sizeof(t_options));
	if (nm->options == NULL)
	{
		ft_dprintf(STDERR_FILENO, MEMORY_FAILED);
		exit(EXIT_ERROR);
	}
	ft_memset(nm->options, 0, sizeof(t_options));
}


int	main(int argc, char **argv) {
	t_nm	nm;

	if (argc == 1) {
		ft_dprintf(STDERR_FILENO, "ft_nm: 'a.out': No such file\n");
		return (ERROR);
	}
	init_struct(&nm);
	if (args_parser(&nm, argc, argv) == -1)
		return (EXIT_ERROR);
	print_options(&nm);
	print_file_list(&nm);
	files_manager(&nm);
	ft_exit(&nm, EXIT_SUCCESS);
}
	