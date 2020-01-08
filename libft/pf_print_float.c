/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 08:01:16 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/05 06:36:19 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	check_flags(long double *n, t_printf *p)
{
	if (*n < 0)
	{
		*n = -*n;
		p->sign = '-';
		p->space = 0;
	}
	if (p->plus && p->sign != '-')
		p->sign = '+';
	if (p->minus)
		p->zero = 0;
	if (p->sign)
		p->width--;
	if (p->space)
		p->width--;
}

static void	handle_zeros(t_printf *p, char *str)
{
	if (p->zero)
	{
		if (p->space && !p->minus)
			pf_buffer(p, " ", 1);
		if (p->sign)
			pf_buffer(p, &p->sign, 1);
		pf_padding(p, p->width - ft_strlen(str), '0');
	}
	if (!p->zero && p->width && !p->minus)
	{
		if (p->space && p->sign == 0 && p->precision_present)
			pf_buffer(p, " ", 1);
		pf_padding(p, p->width - ft_strlen(str), ' ');
		if (p->sign)
			pf_buffer(p, &p->sign, 1);
	}
}

static int	handle_minus(t_printf *p, char *str)
{
	if (p->minus)
	{
		if (p->space)
		{
			pf_buffer(p, " ", 1);
			p->width--;
		}
		if (p->sign)
			pf_buffer(p, &p->sign, 1);
		pf_buffer(p, str, ft_strlen(str));
		if (p->precision_present && p->precision == 0 \
		&& str[0] != '0' && p->hash)
		{
			pf_buffer(p, ".", 1);
			p->width--;
		}
		if (p->width)
		{
			if (p->space)
				p->width++;
			pf_padding(p, p->width - ft_strlen(str), ' ');
		}
		return (1);
	}
	return (0);
}

static void	handle_prec0(t_printf *p, long double n, char str[MAX_F_SIZE])
{
	if (p->precision_present && p->precision == 0)
	{
		pf_ftoa(p, n, str, 1);
		if (str[ft_strlen(str) - 1] >= '5')
		{
			str[ft_strlen(str) - 3]++;
		}
		pf_cut_left(str, ft_strlen(str) - 2);
	}
}

void		pf_print_float(t_printf *p, va_list args)
{
	long double	n;
	char		str[MAX_F_SIZE];

	if (!p->precision_present)
		p->precision = 6;
	n = pf_args_float(args, p);
	check_flags(&n, p);
	pf_ftoa(p, n, str, p->precision);
	handle_zeros(p, str);
	if (handle_minus(p, str))
		return ;
	handle_prec0(p, n, str);
	pf_buffer(p, str, ft_strlen(str));
	if (p->precision_present && p->precision == 0 && str[0] != '0' && p->hash)
	{
		p->width--;
		pf_buffer(p, ".", 1);
	}
	ft_bzero(str, MAX_F_SIZE);
	return ;
}
