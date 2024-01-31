/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:19:11 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/01/28 09:33:11 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

int	ft_printf_all(const char *s, va_list va)
{
	if (!*s)
		return (0);
	if (*s == 'c')
		return (ft_putchar_fd((char)va_arg(va, int), STDERR_FILENO));
	else if (*s == 's')
		return (ft_printf_s(va_arg(va, char *)));
	else if (*s == 'p')
		return (ft_printf_s("0x")
			+ put_base_ul("0123456789abcdef", va_arg(va, unsigned long)));
	else if (*s == 'd' || *s == 'i')
		return (put_base_i("0123456789", va_arg(va, int)));
	else if (*s == 'u')
		return (put_base_ul("0123456789", va_arg(va, unsigned int)));
	else if (*s == 'x')
		return (put_base_ul("0123456789abcdef", va_arg(va, unsigned int)));
	else if (*s == 'X')
		return (put_base_ul("0123456789ABCDEF", va_arg(va, unsigned int)));
	else if (*s == '%')
		return (ft_putchar_fd('%', STDERR_FILENO));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	print_args;
	int		count;

	count = 0;
	va_start(print_args, format);
	while (*format)
	{
		if (*format != '%')
		{
			ft_putchar_fd(*format, STDERR_FILENO);
			count++;
		}
		else
			count += ft_printf_all(++format, print_args);
		if (*format)
			format++;
	}
	va_end(print_args);
	return (count);
}
