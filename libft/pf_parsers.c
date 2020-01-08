/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parsers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 09:49:19 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/06 16:14:31 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	switch_type(const char *str, t_printf *p, va_list args)
{
	char c;

	c = str[p->i];
	if (c == 'd' || c == 'i' || c == 'D')
		pf_print_decimal(p, args);
	else if (c == 'c' || c == 'C')
		pf_print_char(p, args);
	else if (c == 's' || c == 'S')
		pf_print_string(p, args);
	else if (c == 'p' || c == 'P')
		pf_print_pointer(p, args);
	else if (c == 'f' || c == 'F')
		pf_print_float(p, args);
	else if (c == 'x' || c == 'X')
		pf_print_hex(c, p, args);
	else if (c == 'u' || c == 'U')
		pf_print_uint(p, args);
	else if (c == 'o' || c == 'O')
		pf_print_octal(p, args);
	else if (c == 'b' || c == 'B')
		pf_print_binary(p, args);
	else if (c == '%')
		pf_print_percent(p);
	else
		return ;
}

static int	parse_optionals(const char *str, t_printf *p, va_list args)
{
	pf_parse_flags(str, p);
	pf_parse_width(str, p, args);
	pf_parse_precision(str, p, args);
	pf_parse_length(str, p);
	return (0);
}

int			pf_parse_format_string(const char *format,\
		t_printf *p, va_list args)
{
	while (format[p->i] != '\0' && p->bytes != -1)
	{
		if (format[p->i] == '%')
		{
			p->i++;
			if (format[p->i] == '\0')
				return (0);
			if (ft_strchr(OPTIONALS, format[p->i]))
				parse_optionals(format, p, args);
			if (ft_strchr(SPECIFIERS, format[p->i]))
				switch_type(format, p, args);
			else
				return (0);
			pf_reset_struct(p);
		}
		else
			pf_buffer(p, (char *)&format[p->i], 1);
		p->i++;
	}
	if (p->bytes == -1)
		p->bytes += write(1, p->cpy, p->i);
	else
		p->bytes += write(1, p->cpy, p->buff_i);
	return (1);
}
