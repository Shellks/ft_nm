/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:36:47 by acarlott          #+#    #+#             */
/*   Updated: 2025/01/20 14:45:52 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_putchar(char s);
static int	ft_putstr(char *str);
static int	ft_putnbr_int(int n);
static int	ft_putnbr_unsigned(unsigned int n);
static int	ft_print_memory(unsigned long nbr);
static int	ft_check_convert(char str, va_list ap);
static int	ft_putnbr_base(unsigned int nbr, char str);

// --------------------> Printf head function <--------------------------- //


int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (write(1, 0, 0) == -1)
		return (-1);
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			i++;
			count += ft_check_convert(format[i], ap);
		}
		else if (format[i] == '%' && format[i + 1] == '\0')
			break ;
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(ap);
	return (count);
}

// --------------------> Symbols parser <--------------------------- //

static int	ft_check_convert(char str, va_list ap)
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

// --------------------> utils Function <--------------------------- //

static int	ft_putchar(char s)
{
	write(1, &s, 1);
	return (1);
}

static int	ft_putstr(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str == NULL)
		return (ft_putstr("(null)"));
	while (str[i])
	{
		count += ft_putchar(str[i]);
		i++;
	}
	return (count);
}

static int	ft_print_memory(unsigned long nbr)
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

static int	ft_putnbr_int(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		count += ft_putstr("-2147483648");
		return (11);
	}
	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
		count++;
	}
	if (n > 9)
		count += ft_putnbr_int(n / 10);
	count += ft_putchar(n % 10 + '0');
	return (count);
}

static int	ft_putnbr_unsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n > 9)
		count += ft_putnbr_unsigned(n / 10);
	count += ft_putchar(n % 10 + '0');
	return (count);
}

static int	ft_putnbr_base(unsigned int nbr, char str)
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

// ---------------------------------------><--------------------------------------------------- //
