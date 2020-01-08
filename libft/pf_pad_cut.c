/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad_cut.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:48:51 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/05 06:36:19 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_padding(t_printf *p, int len, char c)
{
	if (len <= 0)
		return ;
	while (len-- > 0)
		pf_buffer(p, &c, 1);
	return ;
}

char	*pf_pad_string(char *str, int size, char c)
{
	char	*new;
	int		len;

	if (size <= 0)
		return (ft_strnew(1));
	len = ft_strlen(str);
	if (!(new = ft_strnew(len + size)))
		return (ft_strnew(1));
	ft_memset(new, c, size);
	ft_memcpy(new + size, str, len);
	return (new);
}

void	pf_cut_left(char *str, int cut_left)
{
	if (cut_left <= 0)
		return ;
	ft_memset(str + cut_left, 0, cut_left);
	ft_memmove(str, str, cut_left);
}
