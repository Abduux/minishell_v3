/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr_base.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:19:08 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/01/31 22:52:35 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int fd, char *base, unsigned long nbr, unsigned long baselong)
{
	int	count;

	count = 1;
	if (nbr >= baselong)
	{
		count += ft_putnbr(fd, base, nbr / baselong, baselong);
	}
	ft_putchar_fd(base[nbr % baselong], fd);
	return (count);
}

int	put_base_ul(int fd, char *base, unsigned long ul_decimal)
{
	int	base_len;

	base_len = ft_strlen(base);
	if (base_len == 0)
		return (0);
	return (ft_putnbr(fd, base, ul_decimal, base_len));
}

int	put_base_i(int fd, char *base, int i_decimal)
{
	int		base_len;
	int		is_minus;
	long	l_decimal;

	is_minus = 0;
	base_len = ft_strlen(base);
	if (base_len == 0)
		return (0);
	l_decimal = (long)i_decimal;
	if (l_decimal < 0)
	{
		l_decimal *= -1;
		is_minus++;
		ft_putchar_fd('-', fd);
	}
	return (ft_putnbr(fd, base, l_decimal, base_len) + is_minus);
}
