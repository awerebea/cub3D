/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 16:26:06 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/16 15:38:17 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H
# include <stdarg.h>
# include <wchar.h>
# include <sys/types.h>

typedef struct	s_opts
{
	int		width;
	int		prec;
	int		count_already_printed;
	int		e_pow;
	char	flags;
	char	subspec;
	char	spec;
}				t_opts;

int				ft_printf(const char *format, ...);
char			*ft_printf_strchr(const char *s, int c);
char			*ft_printf_strdup(const char *s);
size_t			ft_printf_strlcpy(char *dst, const char *src, size_t size);
int				ft_printf_toupper(int c);
size_t			ft_printf_strlen(const char *s);
char			*f_strupper(char *s);
char			*f_llitoa_base(ssize_t n, int base);
char			*f_ullitoa_base(unsigned long long n, int base);
char			f_isspec(const char *format, int *i, t_opts *opts);
int				f_pars_format(va_list ap, const char *format);
int				f_print_argument(va_list ap, t_opts *opts);
int				f_print_char(va_list ap, t_opts *opts);
int				f_print_str(va_list ap, t_opts *opts);
int				f_print_int(va_list ap, t_opts *opts);
int				f_print_ptr_uns_hex_oct(va_list ap, t_opts *opts);
size_t			f_check_u_o_x_subspec(va_list ap, t_opts *opts);
int				f_print_float_scientific(va_list ap, t_opts *opts);
int				f_print_percent(t_opts *opts);
int				f_print_e_pow(t_opts *opts);
int				f_print_sign(t_opts *opts, long double val);
int				f_putchar_count(char c, int fd);
int				f_putstr_count(char *s, int fd);
int				f_save_count_printed(va_list ap, t_opts *opts);
t_opts			f_init_opts(int count);

#endif
