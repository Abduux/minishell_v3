/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 19:20:45 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/01/09 13:03:18 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	get_digits_number(int n)
{
	int			i;
	long int	un;

	un = n;
	i = 1;
	if (un < 0)
	{
		i++;
		un *= -1;
	}
	while (un > 9)
	{
		un /= 10;
		i++;
	}
	return (i);
}

void	set_itoa(int n, char *s)
{
	long int	un;

	un = n;
	if (un < 0)
		un *= -1;
	if (un > 9)
	{
		set_itoa(un / 10, s - 1);
	}
	*s = 48 + (un % 10);
}

char	*ft_itoa(int n)
{
	int		str_len;
	char	*str;

	str_len = get_digits_number(n);
	str = (char *)(malloc(str_len + 1));
	if (!str)
		return (NULL);
	set_itoa(n, str + str_len - 1);
	str[str_len] = 0;
	if (n < 0)
		str[0] = '-';
	return (str);
}
