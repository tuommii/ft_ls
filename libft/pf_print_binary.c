/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_binary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 14:20:01 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/05 06:36:19 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_print_binary(t_printf *p, va_list args)
{
	uintmax_t	n;
	char		*str;

	n = pf_args_unum(args, p);
	str = ft_uitoa_base(n, 2, "01", 0);
	pf_buffer(p, str, ft_strlen(str));
	ft_strdel(&str);
}
