/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:34:38 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/05 06:31:03 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	skip_digits(const char *str, t_printf *p)
{
	while (ft_isdigit(str[p->i]))
		p->i++;
}

void		pf_parse_length(const char *str, t_printf *p)
{
	if (ft_strchr(LENGTH, str[p->i]))
	{
		if (str[p->i] == 'h')
			if (str[p->i + 1] == 'h')
				p->length = HH;
			else
				p->length = H;
		else if (str[p->i] == 'l')
			if (str[p->i + 1] == 'l')
				p->length = LL;
			else
				p->length = L;
		else if (str[p->i] == 'L')
			p->length = LLL;
		else if (str[p->i] == 'j')
			p->length = J;
		else if (str[p->i] == 'z')
			p->length = Z;
		else if (str[p->i] == 't')
			p->length = T;
		while (ft_strchr(LENGTH, str[p->i]))
			p->i++;
	}
}

void		pf_parse_width(const char *str, t_printf *p, va_list args)
{
	int w;

	w = 0;
	if (str[p->i] == '*')
	{
		p->asterisk = 1;
		w = va_arg(args, int);
		if (w < 0)
		{
			p->minus = 1;
			w = -w;
		}
		p->width = w;
		p->i++;
	}
	if (ft_isdigit(str[p->i]))
	{
		p->width = ft_atoi(&str[p->i]);
		skip_digits(str, p);
	}
}

void		pf_parse_precision(const char *str, t_printf *p, va_list args)
{
	int	prec;

	prec = 0;
	if (str[p->i] == '.')
	{
		p->precision_present = 1;
		p->i++;
		if (ft_isdigit(str[p->i]))
		{
			p->precision = ft_atoi(&str[p->i]);
			skip_digits(str, p);
		}
		else if (str[p->i] == '*')
		{
			p->asterisk = 1;
			prec = va_arg(args, int);
			if (prec < 0)
				p->asterisk = 2;
			p->precision = (prec < 0) ? p->width : prec;
			skip_digits(str, p);
			p->i++;
		}
	}
}

void		pf_parse_flags(const char *s, t_printf *p)
{
	char c;

	while (ft_strchr(FLAGS, s[p->i]))
	{
		c = s[p->i];
		if (c == '-')
			p->minus = 1;
		else if (c == '+')
			p->plus = 1;
		else if (c == ' ')
			p->space = 1;
		else if (c == '0')
			p->zero = 1;
		else if (c == '#')
			p->hash = 1;
		p->i++;
	}
	if (p->minus)
		p->zero = 0;
}
