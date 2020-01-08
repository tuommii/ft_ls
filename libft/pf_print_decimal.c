/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_decimal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 10:24:39 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/05 06:36:19 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	decide_sign(intmax_t n, t_printf *p, int *str_len)
{
	if (n < 0)
		p->sign = '-';
	else if (n >= 0 && p->plus)
		p->sign = '+';
	else if (p->space && n >= 0)
		p->sign = ' ';
	else
		p->sign = 0;
	if (p->sign != 0)
		*str_len += 1;
	return (*str_len);
}

static int	print_minus(t_printf *p, char *str, int len)
{
	if (p->minus)
	{
		pf_print_sign(p);
		if (!(p->precision_present && p->precision == 0))
			pf_buffer(p, str, ft_strlen(str));
		else
			p->width++;
		pf_padding(p, (p->width - len), ' ');
		return (1);
	}
	return (0);
}

static void	print_width(t_printf *p, int len)
{
	if (p->width > 0)
	{
		if (!p->zero)
		{
			pf_padding(p, p->width - len, ' ');
			pf_print_sign(p);
		}
		else
		{
			pf_print_sign(p);
			pf_padding(p, p->width - len, '0');
		}
	}
}

static int	handle_prec_and_zero(t_printf *p, char *str)
{
	if (str[0] == '0' && p->precision_present && p->precision == 0)
	{
		str[0] = '\0';
		if (p->sign)
			p->width--;
		if (!p->minus)
			pf_padding(p, p->width, ' ');
		pf_print_sign(p);
		if (p->minus)
			pf_padding(p, p->width, ' ');
		return (1);
	}
	if (str[0] == 0 && !p->precision_present)
	{
		str[0] = '0';
		pf_buffer(p, "0", 1);
		return (1);
	}
	return (0);
}

void		pf_print_decimal(t_printf *p, va_list args)
{
	intmax_t	n;
	char		str[MAX_F_SIZE];
	char		*temp;
	int			len;

	p->zero = (p->precision_present) ? 0 : p->zero;
	n = pf_args_num(args, p);
	len = 0;
	decide_sign(n, p, &len);
	n = (n < 0) ? -n : n;
	temp = ft_uitoa_base((uintmax_t)n, 10, "0123456789", p->precision);
	ft_strcpy(str, temp);
	ft_strdel(&temp);
	if (handle_prec_and_zero(p, str))
		return ;
	len += ft_strlen(str);
	if (print_minus(p, str, len))
		return ;
	len = (p->precision_present && p->precision == 0) ? len - 1 : len;
	print_width(p, len);
	pf_print_sign(p);
	if (!(p->precision_present && p->precision == 0 && n == 0))
		pf_buffer(p, str, ft_strlen(str));
}
