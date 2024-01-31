/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 00:50:50 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/01/09 13:23:04 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	fill_log(char *log, const char *set)
{
	int	i;

	i = 0;
	while (i < 256)
		log[i++] = 0;
	while (*set)
		log[(unsigned int)(*(set++))] = 1;
}

size_t	get_trim_size(char const *s1, char const *set, int *s_index)
{
	char	log[256];
	int		start_pivot;
	int		end_pivot;
	int		i;

	i = 0;
	end_pivot = 0;
	fill_log(log, set);
	while (s1[i] && log[(unsigned int)s1[i]])
		i++;
	start_pivot = i;
	while (s1[i])
	{
		if (log[(unsigned int)s1[i++]])
			end_pivot++;
		else
			end_pivot = 0;
	}
	*s_index = start_pivot;
	return (ft_strlen(s1) - start_pivot - end_pivot + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start_index;
	int		trim_size;
	char	*trim_ptr;

	if (!set || !s1)
		return (0);
	trim_size = get_trim_size(s1, set, &start_index);
	trim_ptr = (char *)(malloc(trim_size));
	if (!trim_ptr)
		return (NULL);
	ft_strlcpy(trim_ptr, s1 + start_index, trim_size);
	return (trim_ptr);
}
