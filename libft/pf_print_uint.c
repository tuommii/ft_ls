/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:28:06 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/05 06:36:19 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_minus(t_printf *p, char *str, int len)
{
	if (p->minus)
	{
		pf_print_sign(p);
		if (!(p->precision_present && p->precision == 0))
			pf_buffer(p, str, len);
		pf_padding(p, (p->width - len), ' ');
		return (1);
	}
	return (0);
}

static void	handle_width_and_prec(t_printf *p, char *str, int len)
{
	if (p->width > 0)
	{
		if (!p->zero)
			pf_padding(p, (p->width - len), ' ');
		else
			pf_padding(p, (p->width - len), '0');
	}
	if (!(p->precision_present && p->precision == 0))
	{
		pf_buffer(p, str, len);
	}
}

void		pf_print_uint(t_printf *p, va_list args)
{
	uintmax_t	n;
	char		*str;
	int			len;

	if (p->precision_present)
		p->zero = 0;
	n = pf_args_unum(args, p);
	len = 0;
	str = ft_uitoa_base(n, 10, "0123456789", p->precision);
	len += ft_strlen(str);
	if (n == 0 && p->precision_present && p->precision == 0)
	{
		pf_padding(p, p->width, ' ');
		ft_strdel(&str);
		return ;
	}
	if (handle_minus(p, str, len))
	{
		ft_strdel(&str);
		return ;
	}
	handle_width_and_prec(p, str, len);
	ft_strdel(&str);
}
