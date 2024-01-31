/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 05:38:37 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/02/18 18:25:35 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	gnl_allocat(char **ptr)
{
	unsigned int	i;

	if (*ptr)
		return (1);
	*ptr = (char *)malloc(U_BUFFER_SIZE + 1);
	if (*ptr == NULL)
		return (0);
	i = 0;
	while (i < U_BUFFER_SIZE + 1)
		(*ptr)[i++] = 0;
	return (1);
}

size_t	lnlen(char *thread, int *linelen)
{
	int	i;

	i = 0;
	if (!thread)
		return (0);
	while (thread[i] && thread[i] != '\n')
		i++;
	if (thread[i] == '\n')
		i++;
	*linelen = i;
	return (i);
}

void	ft_cut_thread(char *dst, const char *src)
{
	unsigned int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	while (dst[i])
		dst[i++] = 0;
}
