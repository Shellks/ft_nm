/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:12:53 by acarlott          #+#    #+#             */
/*   Updated: 2025/01/21 11:23:47 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_nm.h"


void ft_exit(t_nm *nm, int error_code) {
    if (nm->files != NULL) {
        lst_files_clear(&nm->files);
    }
    free(nm->options);
    exit(error_code);
}