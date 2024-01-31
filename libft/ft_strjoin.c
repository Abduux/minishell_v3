/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 00:26:54 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/02/18 18:13:03 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	char	*ret_ptr;

	ptr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (NULL);
	ret_ptr = ptr;
	while (s1 && *s1)
	{
		*ptr = *s1;
		ptr++;
		s1++;
	}
	while (s2 && *s2)
	{
		*ptr = *s2;
		ptr++;
		s2++;
	}
	*ptr = 0;
	return (ret_ptr);
}
