/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 00:25:59 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/16 15:38:30 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"

int				f_putchar_count(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int				f_putstr_count(char *s, int fd)
{
	int		count;

	count = 0;
	while (*s)
		count += f_putchar_count(*s++, fd);
	return (count);
}

size_t			f_check_u_o_x_subspec(va_list ap, t_opts *opts)
{
	size_t	val;

	if (opts->spec == 'p')
		return (va_arg(ap, size_t));
	if (opts->subspec & 12)
		val = (opts->subspec & 4) ? \
			va_arg(ap, unsigned long long) : va_arg(ap, unsigned long);
	else if (opts->subspec & 3 && opts->subspec != 'p')
		val = (opts->subspec & 1) ? \
			(unsigned char)va_arg(ap, unsigned int) : \
			(unsigned short int)va_arg(ap, unsigned int);
	else
		val = va_arg(ap, unsigned int);
	return (val);
}

int				f_print_sign(t_opts *opts, long double val)
{
	if ((opts->flags & 12) && val >= 0)
		return (opts->flags & 8) ? \
		f_putchar_count('+', 1) : f_putchar_count(' ', 1);
	return (val < 0) ? f_putchar_count('-', 1) : 0;
}

char			f_isspec(const char *format, int *i, t_opts *opts)
{
	if (!format[*i])
		return (0);
	if (format[*i] == 'L')
	{
		opts->subspec += 4;
		(*i)++;
	}
	else if (format[*i] == 'l')
	{
		opts->subspec = 8;
		(*i)++;
		if (format[(*i)++] == 'l')
			opts->subspec += 4;
		*i -= (opts->subspec & 4) ? 0 : 1;
	}
	else if (format[*i] == 'h')
	{
		(*i)++;
		opts->subspec = 2;
		if (format[(*i)++] == 'h')
			opts->subspec += 1;
		*i -= (opts->subspec & 1) ? 0 : 1;
	}
	return (ft_printf_strchr("cCspdiuoxXnfFgGeE%", format[*i])) ? \
	format[*i] : 0;
}
