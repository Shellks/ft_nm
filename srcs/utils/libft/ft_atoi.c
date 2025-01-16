/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:07:52 by acarlott          #+#    #+#             */
/*   Updated: 2023/02/28 15:41:31 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

// Convert string into int, limit is the long min/max

static int	ft_check(int sign)
{
	if (sign == 1)
	{
		sign = -1;
		return (sign);
	}
	else
		sign = 0;
	return (sign);
}

long long int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	long long int	calcul;

	i = 0;
	sign = 1;
	calcul = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (calcul != (calcul * 10) / 10)
			return (ft_check(sign));
		calcul = calcul * 10 + str[i] - '0';
		i++;
	}
	return (calcul * sign);
}
