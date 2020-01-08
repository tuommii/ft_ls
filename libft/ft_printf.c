/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 09:40:21 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/05 06:31:03 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		pf_reset_struct(t_printf *p)
{
	p->minus = 0;
	p->space = 0;
	p->plus = 0;
	p->hash = 0;
	p->zero = 0;
	p->precision_present = 0;
	p->precision = 0;
	p->length = 0;
	p->width = 0;
	p->sign = 0;
}

int			ft_printf(const char *format, ...)
{
	t_printf	p;
	va_list		args;

	ft_bzero(&p, sizeof(p));
	pf_reset_struct(&p);
	p.fd = 1;
	p.bytes = 0;
	va_start(args, format);
	if (!ft_strchr(format, '%'))
		p.bytes = write(p.fd, format, ft_strlen(format));
	else
	{
		if (pf_parse_format_string(format, &p, args) == -1)
			p.bytes = -1;
	}
	va_end(args);
	return (p.bytes);
}
