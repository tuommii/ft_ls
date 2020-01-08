/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 22:37:15 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/05 08:22:06 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <stddef.h>
# include "libft.h"

# define FLAGS "-+ #0"
# define OPTIONALS "#-+ .*0123456789hljztL"
# define SPECIFIERS "sSpdDioOuUxXfFcCbB%"
# define HEX_LOWER "0123456789abcdef"
# define HEX_UPPER "0123456789ABCDEF"
# define MAX_F_SIZE 200
# define PF_BUFF_SIZE 200
# define MAX_PRECISION 20
# define LENGTH "hljztL"
# define H	1
# define HH	2
# define L	3
# define LL	4
# define J	5
# define Z	6
# define T	7
# define LLL 8

typedef struct	s_printf
{
	long double	rounders[MAX_PRECISION + 1];
	char		c;
	char		cpy[PF_BUFF_SIZE];
	size_t		buff_i;
	long int	bytes;
	size_t		i;
	int			fd;
	char		sign;

	int			minus;
	int			plus;
	int			space;
	int			zero;
	int			hash;

	int			asterisk;
	int			width;
	int			precision_present;
	int			precision;
	int			length;
}				t_printf;

/*
** ft_printf.c
*/

int				ft_printf(const char *format, ...);
void			pf_reset_struct(t_printf *p);

void			pf_parse_length(const char *str, t_printf *p);
void			pf_parse_width(const char *str, t_printf *p, va_list args);
void			pf_parse_precision(const char *str, t_printf *p, va_list args);
void			pf_parse_flags(const char *s, t_printf *p);
int				pf_parse_format_string(const char *format, t_printf *p, \
				va_list args);

/*
** Printing functions
*/

void			pf_print_decimal(t_printf *p, va_list args);
void			pf_print_char(t_printf *p, va_list args);
void			pf_print_string(t_printf *p, va_list args);
void			pf_print_pointer(t_printf *p, va_list args);
void			pf_print_percent(t_printf *p);
void			pf_print_float(t_printf *p, va_list args);
void			pf_print_uint(t_printf *p, va_list args);
void			pf_print_hex(char c, t_printf *p, va_list args);
void			pf_print_octal(t_printf *p, va_list args);
void			pf_print_binary(t_printf *p, va_list args);

void			pf_align(t_printf *p, char *str);
void			pf_print_sign(t_printf *p);

void			pf_ftoa(t_printf *pf, long double f, char *buf, int precision);

void			pf_buffer(t_printf *p, void *new, size_t size);
void			pf_padding(t_printf *p, int len, char c);
char			*pf_pad_string(char *str, int size, char c);
void			pf_cut_left(char *str, int cut_left);

uintmax_t		pf_args_unum(va_list args, t_printf *p);
intmax_t		pf_args_num(va_list args, t_printf *p);
long double		pf_args_float(va_list args, t_printf *p);

#endif
