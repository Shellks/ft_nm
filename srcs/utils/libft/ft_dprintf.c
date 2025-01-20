#include "../include/libft.h"

static int	ft_dputchar(char c, int fd);
static int	ft_dputstr(char *str, int fd);
static int	ft_dputnbr_int(int n, int fd);
static int	ft_dprint_memory(int fd, unsigned long nbr);
static int	ft_dputnbr_unsigned(unsigned int n, int fd);
static int	ft_check_convert_fd(int fd, char str, va_list ap);
static int	ft_dputnbr_base(unsigned int nbr, char str, int fd);


// --------------------> Dprintf head function <--------------------------- //


int	ft_dprintf(int fd, const char *format, ...)
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
			count += ft_check_convert_fd(fd, format[i], ap);
		}
		else if (format[i] == '%' && format[i + 1] == '\0')
			break ;
		else
			count += ft_dputchar(format[i], fd);
		i++;
	}
	va_end(ap);
	return (count);
}

// --------------------> Symbols parser <--------------------------- //


static int	ft_check_convert_fd(int fd, char str, va_list ap)
{
	int	count;

	count = 0;
	if (str == 'c')
		count = ft_dputchar(va_arg(ap, int), fd);
	else if (str == 's')
		count = ft_dputstr(va_arg(ap, char *), fd);
	else if (str == 'p')
	{
		count = ft_dputstr("0x", fd);
		count += ft_dprint_memory((unsigned long)va_arg(ap, void *), fd);
	}
	else if (str == 'i' || str == 'd')
		count = ft_dputnbr_int(va_arg(ap, int), fd);
	else if (str == 'u')
		count = ft_dputnbr_unsigned(va_arg(ap, unsigned int), fd);
	else if (str == 'x' || str == 'X')
		count = ft_dputnbr_base(va_arg(ap, unsigned int), str, fd);
	else if (str == '%')
		count = ft_dputchar('%', fd);
	return (count);
}

// --------------------> utils Function <--------------------------- //

static int	ft_dputchar(char c, int fd) // Print char in given fd
{
	write(fd, &c, 1);
    return (1);
}

static int	ft_dputstr(char *str, int fd) // Print string in given fd
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str == NULL)
		return (ft_dputstr("(null)", fd));
	while (str[i])
	{
		count += ft_dputchar(str[i], fd);
		i++;
	}
	return (count);
}

static int	ft_dprint_memory(int fd, unsigned long nbr) // Print memory adress in given fd
{
	unsigned long int	nb;
	int					count;
	char				*base;

	nb = nbr;
	count = 0;
	base = "0123456789abcdef";
	if (nb > 15)
		count += ft_dprint_memory(nb / 16, fd);
	count += ft_dputchar(base[nb % 16], fd);
	return (count);
}

static int	ft_dputnbr_int(int n, int fd) // Print int in given fd
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		count += ft_dputstr("-2147483648", fd);
		return (11);
	}
	if (n < 0)
	{
		ft_dputchar('-', fd);
		n *= -1;
		count++;
	}
	if (n > 9)
		count += ft_dputnbr_int(n / 10, fd);
	count += ft_dputchar(n % 10 + '0', fd);
	return (count);
}

static int	ft_dputnbr_unsigned(unsigned int n, int fd) // Print unsigned int in given fd
{
	int	count;

	count = 0;
	if (n > 9)
		count += ft_dputnbr_unsigned(n / 10, fd);
	count += ft_dputchar(n % 10 + '0', fd);
	return (count);
}

static int	ft_dputnbr_base(unsigned int nbr, char str, int fd) // Print int (base 16) in given fd
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
		count += ft_dputnbr_base(nb / 16, str, fd);
	count += ft_dputchar(base[nb % 16], fd);
	return (count);
}

// ---------------------------------------><--------------------------------------------------- //
