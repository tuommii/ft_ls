/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 16:25:24 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/05 06:36:19 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	pf_args_num(va_list args, t_printf *p)
{
	intmax_t n;

	n = va_arg(args, intmax_t);
	if (p->length == HH)
		n = (char)n;
	else if (p->length == H)
		n = (short int)n;
	else if (p->length == L)
		n = (long int)n;
	else if (p->length == LL)
		n = (long long int)n;
	else if (p->length == J)
		n = (intmax_t)n;
	else if (p->length == Z)
		n = (size_t)n;
	else if (p->length == T)
		n = (ptrdiff_t)n;
	else
		n = (int)n;
	return (n);
}

long double	pf_args_float(va_list args, t_printf *p)
{
	long double n;

	if (p->length == LLL)
		n = va_arg(args, long double);
	else
		n = (double)va_arg(args, double);
	return (n);
}

uintmax_t	pf_args_unum(va_list args, t_printf *p)
{
	uintmax_t n;

	n = va_arg(args, uintmax_t);
	if (p->length == HH)
		n = (unsigned char)n;
	else if (p->length == H)
		n = (unsigned short int)n;
	else if (p->length == L)
		n = (unsigned long int)n;
	else if (p->length == LL)
		n = (unsigned long long int)n;
	else if (p->length == J)
		n = (uintmax_t)n;
	else if (p->length == Z)
		n = (size_t)n;
	else if (p->length == T)
		n = (ptrdiff_t)n;
	else
		n = (unsigned int)n;
	return (n);
}
