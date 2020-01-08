/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 07:20:01 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/05 06:36:19 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_print_char(t_printf *p, va_list args)
{
	unsigned char c;

	c = pf_args_unum(args, p);
	if (p->minus)
	{
		pf_buffer(p, &c, 1);
		pf_padding(p, p->width - 1, ' ');
	}
	else
	{
		pf_padding(p, p->width - 1, ' ');
		pf_buffer(p, &c, 1);
	}
}
