/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 01:16:07 by acarlott          #+#    #+#             */
/*   Updated: 2023/01/25 12:58:03 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	if (!dst && !dstsize)
		return (ft_strlen(src));
	while (dst[len] && len < dstsize)
		len++;
	while (src[i] && dstsize && i + len < dstsize - 1)
	{
		dst[len + i] = src[i];
		i++;
	}
	if (len < dstsize)
		dst[len + i] = '\0';
	i = 0;
	while (src[i])
		i++;
	return (len + i);
}
