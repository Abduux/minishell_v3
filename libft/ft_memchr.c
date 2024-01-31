/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 04:56:02 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/04/12 18:21:33 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*_s;

	i = 0;
	_s = (unsigned char *)s;
	while (i < n)
	{
		if (_s[i] == (unsigned char)c)
			return ((void *)(_s + i));
		i++;
	}
	return (0);
}
