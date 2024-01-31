/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:45:51 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/01/05 01:57:25 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	unsigned char	*_src;
	unsigned char	*_dest;

	i = 0;
	_src = (unsigned char *)src;
	_dest = (unsigned char *)dest;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		_dest[i] = _src[i];
		i++;
	}
	return (dest);
}
