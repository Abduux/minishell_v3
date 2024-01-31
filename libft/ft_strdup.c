/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 05:36:05 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/01/10 00:45:18 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	s_len;
	int		i;
	char	*s_dup;

	i = 0;
	s_len = ft_strlen(s);
	s_dup = (char *)malloc(s_len + 1);
	if (!s_dup)
		return (NULL);
	while (s && s[i])
	{
		s_dup[i] = s[i];
		i++;
	}
	s_dup[i] = 0;
	return (s_dup);
}
