/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:28:09 by acarlott          #+#    #+#             */
/*   Updated: 2025/01/16 18:21:45 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_print_memory(unsigned long nbr)
{
	unsigned long int	nb;
	int					count;
	char				*base;

	nb = nbr;
	count = 0;
	base = "0123456789abcdef";
	if (nb > 15)
		count += ft_print_memory(nb / 16);
	count += ft_putchar(base[nb % 16]);
	return (count);
}
