/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:24:28 by acarlott          #+#    #+#             */
/*   Updated: 2023/01/25 12:58:23 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = ((char *)s);
	while (str[i])
		i++;
	while (str[i] != (unsigned char)c && i > 0)
		i--;
	if (str[i] == (unsigned char)c)
		return (&str[i]);
	return (NULL);
}
