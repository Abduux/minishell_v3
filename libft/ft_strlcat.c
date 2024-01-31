/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 02:21:43 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/01/09 13:21:10 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	int		i;

	i = 0;
	dest_len = ft_strlen(dst);
	if (size < dest_len || !size)
		return (ft_strlen(src) + size);
	while (i + dest_len < size - 1 && src[i])
	{
		dst[i + dest_len] = src[i];
		i++;
	}
	dst[i + dest_len] = 0;
	return (dest_len + ft_strlen(src));
}
