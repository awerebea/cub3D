/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_c_s.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 13:45:09 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/15 15:33:34 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

int				f_print_char(va_list ap, t_opts *opts)
{
	int		count;
	char	val;

	count = 0;
	val = va_arg(ap, int);
	if ((opts->subspec & 8) && val < 0)
		return (-1);
	if (opts->width > 1)
	{
		if (opts->flags & 16)
		{
			count += f_putchar_count(val, 1);
			while (count < opts->width)
				count += f_putchar_count(' ', 1);
			return (count);
		}
		while (count < opts->width - 1)
			count += f_putchar_count(' ', 1);
	}
	count += f_putchar_count(val, 1);
	return (count);
}

static int		f_print_assist_str(char *str, t_opts *opts)
{
	int		count;
	int		len;
	int		spaces;
	char	*tmp;

	count = 0;
	len = (int)ft_printf_strlen(str);
	tmp = str;
	if ((opts->flags & 32) && len > opts->prec)
	{
		if (!(tmp = malloc(sizeof(char) * opts->prec + 1)))
			return (-1);
		ft_printf_strlcpy(tmp, str, opts->prec + 1);
	}
	spaces = (len > opts->prec && (opts->flags & 32)) ? \
			opts->width - opts->prec : opts->width - len;
	count += (opts->flags & 16) ? f_putstr_count(tmp, 1) : 0;
	while (spaces-- > 0)
		count += f_putchar_count(' ', 1);
	count += (!(opts->flags & 16)) ? f_putstr_count(tmp, 1) : 0;
	if ((opts->flags & 32) && len > opts->prec)
		free(tmp);
	return (count);
}

int				f_print_str(va_list ap, t_opts *opts)
{
	int		count;
	char	*val;
	char	*str;

	str = NULL;
	val = va_arg(ap, char*);
	str = (!val) ? ft_printf_strdup("(null)") : val;
	if (!str)
		return (-1);
	count = f_print_assist_str(str, opts);
	!val ? free(str) : 0;
	return (count);
}
