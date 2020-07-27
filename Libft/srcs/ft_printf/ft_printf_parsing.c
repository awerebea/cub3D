/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 00:02:15 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/14 11:17:18 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	f_pars_flags(char c, char flags)
{
	if (c == '-' && !(16 & flags))
		flags += 16;
	else if (c == '+' && !(8 & flags))
		flags += 8;
	else if (c == ' ' && !(4 & flags))
		flags += 4;
	else if (c == '#' && !(2 & flags))
		flags += 2;
	else if (c == '0' && !(1 & flags))
		flags += 1;
	return (flags);
}

static int	f_pars_width(va_list ap, const char *format, int *i, t_opts *opts)
{
	int		width;

	width = 0;
	if (format[*i] == '*')
	{
		if ((width = va_arg(ap, int)) < 0)
		{
			width *= -1;
			opts->flags = opts->flags | 16;
			opts->flags = opts->flags & 30;
		}
		*i += 1;
	}
	else
	{
		while (format[*i] >= '0' && format[*i] <= '9')
		{
			if ((width * 10) < width)
				return (-1);
			width = width * 10 + format[*i] - '0';
			*i += 1;
		}
	}
	return (width);
}

static int	f_pars_prec(va_list ap, const char *format, int *i, t_opts *opts)
{
	int		prec;

	prec = 0;
	opts->flags += 32;
	if (format[*i] == '*')
	{
		if ((prec = va_arg(ap, int)) < 0)
		{
			prec = 0;
			opts->flags -= 32;
		}
		*i += 1;
	}
	else
	{
		while (format[*i] >= '0' && format[*i] <= '9')
		{
			if ((prec * 10) < prec)
				return (-1);
			prec = prec * 10 + format[*i] - '0';
			*i += 1;
		}
	}
	return (prec);
}

static int	f_pars_opts(va_list ap, const char *format, int *i, int count)
{
	t_opts	opts;

	opts = f_init_opts(count);
	*i += 1;
	while (ft_printf_strchr("-+ #0", format[*i]))
	{
		if (!(opts.flags = f_pars_flags(format[*i], opts.flags)))
			return (-1);
		*i += 1;
	}
	if (format[*i] == '*' || (format[*i] >= '0' && format[*i] <= '9'))
	{
		if ((opts.width = f_pars_width(ap, format, i, &opts)) < 0)
			return (-1);
	}
	if (format[*i] == '.' && format[*i + 1])
	{
		*i += 1;
		if ((opts.prec = f_pars_prec(ap, format, i, &opts)) < 0)
			return (-1);
	}
	opts.spec = f_isspec(format, i, &opts);
	return (opts.spec != 0) ? (f_print_argument(ap, &opts)) : (-1);
}

int			f_pars_format(va_list ap, const char *format)
{
	int		i;
	int		count;
	int		tmp;

	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] != '%')
			count += f_putchar_count(format[i], 1);
		else if (format[i] == '%' && format[i + 1])
		{
			if ((tmp = f_pars_opts(ap, format, &i, count)) < 0)
				return (-1);
			count += tmp;
		}
		else
			return (-1);
		i++;
	}
	return (count);
}
