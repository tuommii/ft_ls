/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:36:39 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/05 06:36:19 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_align(t_printf *p, char *str)
{
	char	*inv;
	int		len;

	len = ft_strlen(str);
	if (p->minus)
	{
		inv = ft_invert_padding(str, len);
		pf_buffer(p, inv, len);
		ft_strdel(&inv);
	}
	else
		pf_buffer(p, str, len);
}

void	pf_buffer(t_printf *p, void *new, size_t size)
{
	long		new_i;
	int			diff;

	new_i = 0;
	while (PF_BUFF_SIZE - p->buff_i < size)
	{
		diff = PF_BUFF_SIZE - p->buff_i;
		ft_memcpy((char *)(p->cpy + p->buff_i), \
												(char *)(new + new_i), diff);
		size -= diff;
		new_i += diff;
		p->buff_i += diff;
		p->bytes += diff;
		if (write(1, p->cpy, p->buff_i) == -1)
			return ;
		p->buff_i = 0;
	}
	ft_memcpy((char *)(p->cpy + p->buff_i), (char *)(new + new_i), size);
	p->buff_i += size;
}

void	pf_print_sign(t_printf *p)
{
	if (p->sign != 0)
		pf_buffer(p, &p->sign, 1);
	p->sign = 0;
}
