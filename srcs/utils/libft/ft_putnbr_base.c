/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:37:36 by acarlott          #+#    #+#             */
/*   Updated: 2025/01/16 18:21:45 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_putnbr_base(unsigned int nbr, char str)
{
	unsigned int		nb;
	int					count;
	char				*base;

	nb = nbr;
	count = 0;
	if (str == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (nb > 15)
		count += ft_putnbr_base(nb / 16, str);
	count += ft_putchar(base[nb % 16]);
	return (count);
}
