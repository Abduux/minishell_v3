/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 21:58:25 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/01/08 22:19:02 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	un;

	un = n;
	if (un < 0)
	{
		un *= -1;
		ft_putchar_fd('-', fd);
	}
	if (un > 9)
	{
		ft_putnbr_fd(un / 10, fd);
	}
	ft_putchar_fd(48 + (un % 10), fd);
}
