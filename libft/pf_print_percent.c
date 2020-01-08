/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 16:20:17 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/05 06:36:19 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_percent_left(t_printf *p)
{
	pf_buffer(p, "%", 1);
	while (p->width > 1)
	{
		pf_buffer(p, " ", 1);
		p->width--;
	}
}

static void	print_percent_right(t_printf *p)
{
	while (p->width > 1)
	{
		if (p->zero)
			pf_buffer(p, "0", 1);
		else
			pf_buffer(p, " ", 1);
		p->width--;
	}
	pf_buffer(p, "%", 1);
}

void		pf_print_percent(t_printf *p)
{
	if (p->minus)
		print_percent_left(p);
	else
		print_percent_right(p);
}
