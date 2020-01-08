/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 07:45:15 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/05 06:36:19 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_prec0(t_printf *p)
{
	if (p->precision_present && p->precision == 0)
	{
		if (p->minus)
		{
			pf_buffer(p, "0x", 2);
			pf_padding(p, p->width - 2, ' ');
		}
		else
		{
			pf_padding(p, p->width - 2, ' ');
			pf_buffer(p, "0x", 2);
		}
		return (1);
	}
	return (0);
}

static int	handle_0(t_printf *p, uintmax_t n)
{
	if (n == 0)
	{
		if (handle_prec0(p))
			return (1);
		if (p->minus)
		{
			pf_buffer(p, "0x0", 3);
			if (!p->width && p->precision > 1)
				pf_padding(p, p->precision - 1, '0');
			pf_padding(p, p->width - 3, ' ');
		}
		else
		{
			pf_padding(p, p->width - 3, ' ');
			pf_buffer(p, "0x0", 3);
			if (!p->width && p->precision > 1)
				pf_padding(p, p->precision - 1, '0');
		}
		return (1);
	}
	return (0);
}

static void	handle_print(t_printf *p, char *temp)
{
	if (p->minus)
	{
		pf_buffer(p, temp, ft_strlen(temp));
		pf_padding(p, p->width - ft_strlen(temp), ' ');
	}
	else
	{
		pf_padding(p, p->width - ft_strlen(temp), ' ');
		pf_buffer(p, temp, ft_strlen(temp));
	}
}

void		pf_print_pointer(t_printf *p, va_list args)
{
	uintmax_t	n;
	char		*str;
	char		*temp;
	int			len;

	n = (long long)va_arg(args, void *);
	if (handle_0(p, n))
		return ;
	str = ft_uitoa_base(n, 16, "0123456789abcdef", 0);
	len = ft_strlen(str);
	if (p->precision && p->precision > p->width)
	{
		temp = pf_pad_string(str, p->precision - len, '0');
		if (str != NULL)
			ft_strdel(&str);
		str = temp;
	}
	temp = ft_strjoin("0x", str);
	ft_strdel(&str);
	handle_print(p, temp);
	ft_strdel(&temp);
}
