/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_convert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:50:17 by acarlott          #+#    #+#             */
/*   Updated: 2025/01/16 18:20:57 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_check_convert(char str, va_list ap)
{
	int	count;

	count = 0;
	if (str == 'c')
		count = ft_putchar(va_arg(ap, int));
	else if (str == 's')
		count = ft_putstr(va_arg(ap, char *));
	else if (str == 'p')
	{
		count = ft_putstr("0x");
		count += ft_print_memory((unsigned long)va_arg(ap, void *));
	}
	else if (str == 'i' || str == 'd')
		count = ft_putnbr_int(va_arg(ap, int));
	else if (str == 'u')
		count = ft_putnbr_unsigned(va_arg(ap, unsigned int));
	else if (str == 'x' || str == 'X')
		count = ft_putnbr_base(va_arg(ap, unsigned int), str);
	else if (str == '%')
		count = ft_putchar('%');
	return (count);
}
