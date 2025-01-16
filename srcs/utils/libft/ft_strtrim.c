/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 01:28:23 by acarlott          #+#    #+#             */
/*   Updated: 2023/01/25 12:58:25 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_check(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	len;
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	if (s1 == 0 || set == 0)
		return (NULL);
	len = (ft_strlen (s1));
	while (ft_check(s1[j], set))
		j++;
	while (ft_check(s1[len - 1], set) && j < len)
		len--;
	str = (char *)malloc(sizeof(char) * (len - j + 1));
	if (!str)
		return (NULL);
	while (j < len)
	{
		str[i] = s1[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
