/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 05:43:10 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/01/09 13:23:30 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub_s;
	unsigned int	i;
	unsigned int	s_len;
	unsigned int	start_len;

	i = 0;
	s_len = ft_strlen(s);
	start_len = 0;
	if (start < s_len)
		start_len = ft_strlen(s + start);
	if (s_len < start)
		len = 0;
	if (len > start_len)
		len = start_len;
	sub_s = (char *)malloc(len + 1);
	if (!sub_s)
		return (NULL);
	while (start + i < s_len && s[start + i] && i < len)
	{
		sub_s[i] = s[start + i];
		i++;
	}
	sub_s[i] = 0;
	return (sub_s);
}
