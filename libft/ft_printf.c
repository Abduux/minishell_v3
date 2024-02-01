/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:19:11 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/01/31 23:03:23 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

int	put_base_ul(int fd, char *base, unsigned long ul_decimal);
int	put_base_i(int fd, char *base, int i_decimal);

static int	ft_printf_s(int fd, const char *s)
{
	int	count;

	count = 0;
	if (!s)
	{
		ft_putstr_fd("(null)", fd);
		return (6);
	}
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
		count++;
	}
	return (count);
}

static int	ft_printf_all(int fd, const char *s, va_list va)
{
	if (!*s)
		return (0);
	if (*s == 'c')
		return (ft_putchar_fd((char)va_arg(va, int), fd));
	else if (*s == 's')
		return (ft_printf_s(fd, va_arg(va, char *)));
	else if (*s == 'p')
		return (ft_printf_s(fd, "0x")
			+ put_base_ul(fd, "0123456789abcdef", va_arg(va, unsigned long)));
	else if (*s == 'd' || *s == 'i')
		return (put_base_i(fd, "0123456789", va_arg(va, int)));
	else if (*s == 'u')
		return (put_base_ul(fd, "0123456789", va_arg(va, unsigned int)));
	else if (*s == 'x')
		return (put_base_ul(fd, "0123456789abcdef", va_arg(va, unsigned int)));
	else if (*s == 'X')
		return (put_base_ul(fd, "0123456789ABCDEF", va_arg(va, unsigned int)));
	else if (*s == '%')
		return (ft_putchar_fd('%', fd));
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
			ft_putchar_fd(*format, 1);
			count++;
		}
		else
			count += ft_printf_all(STDOUT_FILENO, ++format, print_args);
		if (*format)
			format++;
	}
	va_end(print_args);
	return (count);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	print_args;
	int		count;

	count = 0;
	va_start(print_args, format);
	while (*format)
	{
		if (*format != '%')
		{
			ft_putchar_fd(*format, fd);
			count++;
		}
		else
			count += ft_printf_all(fd, ++format, print_args);
		if (*format)
			format++;
	}
	va_end(print_args);
	return (count);
}
