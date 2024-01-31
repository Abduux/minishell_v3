/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:42:32 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/01/09 13:17:23 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*_dest;
	unsigned char	*_src;
	unsigned int	i;

	_dest = (unsigned char *)dest;
	_src = (unsigned char *)src;
	i = n;
	if (!dest && !src)
		return (0);
	if (dest == src)
		return (dest);
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	while (i > 0)
	{
		i--;
		_dest[i] = _src[i];
	}
	return (dest);
}
