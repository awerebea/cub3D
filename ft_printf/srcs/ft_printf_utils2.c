/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 20:10:12 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/14 17:06:01 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

char			*f_llitoa_base(ssize_t n, int base)
{
	char		*str;
	char		*symbols;
	int			i;
	ssize_t		m;
	size_t		num;

	if ((base < 2 || base > 16) || (base != 10 && n < 0))
		return (NULL);
	if (n == 0)
		return (ft_printf_strdup("0"));
	i = (n < 0) ? 2 : 1;
	m = n;
	while (m /= base)
		i++;
	if (!(symbols = ft_printf_strdup("0123456789abcdef")) || \
			!(str = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	(n < 0) ? str[0] = '-' : 0;
	num = (n < 0) ? ((size_t)n * -1) : (size_t)n;
	str[i--] = '\0';
	str[i--] = symbols[num % base];
	while (num /= base)
		str[i--] = symbols[num % base];
	free(symbols);
	return (str);
}

char			*f_ullitoa_base(unsigned long long n, int base)
{
	char				*str;
	char				*symbols;
	int					i;
	long long			m;
	unsigned long long	num;

	if (base < 2 || base > 16)
		return (NULL);
	if (n == 0)
		return (ft_printf_strdup("0"));
	i = 1;
	m = n;
	while (m /= base)
		i++;
	if (!(symbols = ft_printf_strdup("0123456789abcdef")) || \
			!(str = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	num = n;
	str[i--] = '\0';
	str[i--] = symbols[num % base];
	while (num /= base)
		str[i--] = symbols[num % base];
	free(symbols);
	return (str);
}

char			*f_strupper(char *s)
{
	int				len;
	char			*dest;

	len = ft_printf_strlen(s);
	if (!(dest = malloc((sizeof(char) * len + 1))))
		return (NULL);
	while (*s)
		*dest++ = ft_printf_toupper(*s++);
	*dest = '\0';
	free(s - len);
	return (dest - len);
}

int				f_save_count_printed(va_list ap, t_opts *opts)
{
	int				*count_printed;

	count_printed = va_arg(ap, int*);
	*count_printed = opts->count_already_printed;
	return (0);
}

int				f_print_e_pow(t_opts *opts)
{
	int				count;
	int				len;
	char			*s;

	count = 0;
	if (opts->spec == 'e')
		count += f_putchar_count('e', 1);
	else if (opts->spec == 'E')
		count += f_putchar_count('E', 1);
	count += (opts->e_pow < 0) ? \
			f_putchar_count('-', 1) : f_putchar_count('+', 1);
	if (opts->e_pow > -10 && opts->e_pow < 10)
		count += f_putchar_count('0', 1);
	if (!(s = f_llitoa_base(opts->e_pow, 10)))
		return (-1);
	len = ft_printf_strlen(s);
	if (opts->e_pow < 0)
	{
		s++;
		len--;
	}
	count += f_putstr_count(s, 1);
	(opts->e_pow < 0) ? free(--s) : free(s);
	return (count);
}
