/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 07:31:26 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/05 06:36:19 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_width(t_printf *p, int len, char **str, char **temp)
{
	if (p->width)
	{
		if (!p->minus)
			pf_padding(p, p->width - len, (p->zero && !p->minus) ? '0' : ' ');
		if (p->precision > 0)
		{
			*temp = ft_strnew(p->precision);
			ft_strncpy(*temp, *str, p->precision);
			pf_buffer(p, *temp, ft_strlen(*temp));
			ft_strdel(temp);
		}
		else
			pf_buffer(p, *str, ft_strlen(*str));
		if (p->minus)
			pf_padding(p, p->width - len, (p->zero && !p->minus) ? '0' : ' ');
		return (1);
	}
	return (0);
}

static int	check_flags(t_printf *p, char **str, int *len)
{
	if (!*str)
		*len = 6;
	if (p->precision > 0 && p->precision < *len && *len > 0)
		*len -= (*len - p->precision);
	if (p->precision_present && p->precision == 0)
	{
		if (p->width)
			pf_padding(p, p->width, ' ');
		else
			pf_padding(p, 0, '\0');
		return (1);
	}
	if (!*str)
	{
		*str = "(null)";
		if (p->precision_present && p->precision == 0 && p->width)
		{
			*str = "";
			p->width += 6;
		}
	}
	return (0);
}

static int	handle_asterisk(t_printf *p, int len, char *str)
{
	if (p->precision_present && p->precision == 0 && p->asterisk)
	{
		if (p->asterisk == 2)
		{
			if (p->width > len)
				pf_padding(p, p->width - len, '0');
			pf_buffer(p, str, len);
			return (1);
		}
		if (p->width > len)
			pf_padding(p, p->width - len, ' ');
		pf_buffer(p, str, p->width);
		return (1);
	}
	return (0);
}

void		pf_print_string(t_printf *p, va_list args)
{
	char	*str;
	char	*temp;
	int		len;

	str = va_arg(args, char *);
	len = (str) ? ft_strlen(str) : 0;
	if (handle_asterisk(p, len, str))
		return ;
	if (check_flags(p, &str, &len))
		return ;
	if (handle_width(p, len, &str, &temp))
		return ;
	if (!p->width)
	{
		if (p->precision > 0)
		{
			temp = ft_strnew(p->precision);
			ft_strncpy(temp, str, p->precision);
			pf_buffer(p, temp, ft_strlen(temp));
			ft_strdel(&temp);
			return ;
		}
	}
	pf_buffer(p, str, ft_strlen(str));
}
