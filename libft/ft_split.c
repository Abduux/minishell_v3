/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 03:42:30 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/04/11 21:27:00 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_strs_num(const char *s, char c)
{
	int	strs_num;

	if (!s)
		return (0);
	strs_num = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		if (*s != c)
		{
			strs_num++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (strs_num);
}

void	ft_strcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (!size)
		return ;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
}

char	**ft_split(char const *s, char c)
{
	int		strs_num;
	int		i;
	int		j;
	char	**split_strs;

	strs_num = get_strs_num(s, c);
	split_strs = (char **)(malloc((strs_num + 1) * sizeof(char *)));
	if (!split_strs || !s)
		return (NULL);
	i = 0;
	while (i < strs_num)
	{
		while (*s && *s == c)
			s++;
		j = 0;
		while (s[j] && s[j] != c)
			j++;
		split_strs[i] = (char *)(malloc(j + 1));
		ft_strcpy(split_strs[i], s, j + 1);
		s += j;
		i++;
	}
	split_strs[i] = 0;
	return (split_strs);
}
