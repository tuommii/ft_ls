/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_octal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 10:42:07 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/05 06:36:19 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_prec0(t_printf *p, uintmax_t n, char **str, char **temp)
{
	if (p->precision_present && p->precision == 0 && n == 0)
	{
		if (!p->hash)
		{
			pf_padding(p, p->width, ' ');
			return (1);
		}
		if (!p->width)
		{
			pf_buffer(p, "0", 1);
			return (1);
		}
		*temp = "0";
		*str = pf_pad_string(*temp, p->width - p->hash, ' ');
		if (p->hash)
			pf_align(p, *str);
		ft_strdel(str);
		return (1);
	}
	return (0);
}

static int	handle_prec(t_printf *p, uintmax_t n, char **str, char **temp)
{
	if (p->precision_present && n == 0 && p->precision > 0)
	{
		*temp = "";
		*temp = pf_pad_string(*temp, p->precision, '0');
		if (p->width > p->precision)
		{
			*str = pf_pad_string(*temp, p->width - p->precision, ' ');
			pf_align(p, *str);
			ft_strdel(str);
		}
		else
		{
			pf_align(p, *temp);
		}
		ft_strdel(temp);
		return (1);
	}
	return (0);
}

static void	check_flags(t_printf *p, int *len)
{
	if (p->precision_present)
		p->zero = 0;
	if (p->hash && p->width >= *len && !p->precision)
		*len += 1;
	if (p->hash && p->width >= *len && p->precision_present \
	&& p->precision < *len)
		*len += 1;
}

static int	handle_width(t_printf *p, int len, char **str, char **temp)
{
	if (p->precision > 0 && p->precision > len)
	{
		*temp = pf_pad_string(*str, p->precision - len - p->hash, '0');
		ft_strdel(str);
		*str = *temp;
		if (p->precision > p->width)
		{
			pf_align(p, *str);
			ft_strdel(str);
			return (1);
		}
	}
	if (p->width > len)
	{
		*temp = pf_pad_string(*str, p->width - ft_strlen(*str), \
		(p->zero) ? '0' : ' ');
		ft_strdel(str);
		*str = *temp;
	}
	return (0);
}

void		pf_print_octal(t_printf *p, va_list args)
{
	uintmax_t	n;
	char		*str;
	char		*temp;
	int			len;

	n = pf_args_unum(args, p);
	if (handle_prec0(p, n, &str, &temp))
		return ;
	if (handle_prec(p, n, &str, &temp))
		return ;
	str = ft_uitoa_base(n, 8, "01234567", 0);
	len = ft_strlen(str);
	check_flags(p, &len);
	if (p->hash && n != 0)
	{
		temp = pf_pad_string(str, 1, '0');
		ft_strdel(&str);
		str = temp;
	}
	if (handle_width(p, len, &str, &temp))
		return ;
	pf_align(p, str);
	ft_strdel(&str);
}
