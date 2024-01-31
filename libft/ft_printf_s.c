/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:19:04 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/01/13 17:10:22 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_s(const char *s)
{
	int	count;

	count = 0;
	if (!s)
	{
		ft_putstr_fd("(null)", STDERR_FILENO);
		return (6);
	}
	while (*s)
	{
		ft_putchar_fd(*s, STDERR_FILENO);
		s++;
		count++;
	}
	return (count);
}
