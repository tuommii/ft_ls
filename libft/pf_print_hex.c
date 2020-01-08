/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 20:56:40 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/06 16:15:04 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	handle_width(t_printf *p, int size)
{
	if (p->width)
	{
		if (size < p->width && p->precision > 0 && !p->minus)
			pf_padding(p, p->width - size, ' ');
		if (!p->zero && !p->precision && !p->minus)
			pf_padding(p, p->width - size, ' ');
		if (p->hash)
			pf_buffer(p, (p->c == 'X') ? "0X" : "0x", 2);
		if ((p->zero && !(size < p->width)) || (p->zero && !p->precision))
			pf_padding(p, p->width - size, '0');
	}
}

static void	handle_prec(t_printf *p, char **str, uintmax_t n)
{
	if (p->precision_present && p->precision == 0 && n == 0)
	{
		ft_strdel(str);
		*str = ft_strnew(1);
		p->width++;
		p->hash = 0;
	}
}

static int	pf_max(int a, int b)
{
	if (b > a)
		return (b);
	else
		return (a);
}

void		pf_print_hex(char c, t_printf *p, va_list args)
{
	uintmax_t	n;
	char		*str;
	int			size;

	n = pf_args_unum(args, p);
	str = ft_uitoa_base(n, 16, (c == 'X') \
	? HEX_UPPER : HEX_LOWER, p->precision);
	size = ft_strlen(str);
	p->c = c;
	if (n == 0)
		p->hash = 0;
	size = pf_max(size, p->precision);
	handle_prec(p, &str, n);
	if (p->hash)
		size += 2;
	handle_width(p, size);
	if (!p->width && p->hash)
		pf_buffer(p, (p->c == 'X') ? "0X" : "0x", 2);
	pf_buffer(p, str, ft_strlen(str));
	if (p->minus && size < p->width)
		pf_padding(p, p->width - size, ' ');
	ft_strdel(&str);
}
