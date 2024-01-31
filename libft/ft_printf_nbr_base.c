/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr_base.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:19:08 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/01/28 09:27:24 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(char *base, unsigned long nbr, unsigned long baselong)
{
	int	count;

	count = 1;
	if (nbr >= baselong)
	{
		count += ft_putnbr(base, nbr / baselong, baselong);
	}
	ft_putchar_fd(base[nbr % baselong], STDERR_FILENO);
	return (count);
}

int	put_base_ul(char *base, unsigned long ul_decimal)
{
	int	base_len;

	base_len = ft_strlen(base);
	if (base_len == 0)
		return (0);
	return (ft_putnbr(base, ul_decimal, base_len));
}

int	put_base_i(char *base, int i_decimal)
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
		ft_putchar_fd('-', STDERR_FILENO);
	}
	return (ft_putnbr(base, l_decimal, base_len) + is_minus);
}
