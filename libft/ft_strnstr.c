/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 23:24:16 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/01/09 13:22:23 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *target, size_t len)
{
	unsigned int	i;
	unsigned int	n;

	i = 0;
	n = 0;
	if (!target[i])
		return ((char *)s);
	while (s[n] && n < len)
	{
		i = 0;
		while (s[n + i] && target[i] && s[n + i] == target[i] && n + i < len)
		{
			if (!target[i + 1])
				return ((char *)(s + n));
			i++;
		}
		n++;
	}
	return (0);
}
