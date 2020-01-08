/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pad_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 09:35:09 by mtuomine          #+#    #+#             */
/*   Updated: 2019/11/18 09:28:42 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_pad_left(char *str, int total_width, char c)
{
	int		i;
	int		len;
	char	*new;

	len = ft_strlen(str);
	if (len >= total_width)
		return (str);
	new = ft_strnew(total_width);
	i = 0;
	while (i < (total_width - len))
		new[i++] = c;
	while (i < total_width)
		new[i++] = *str++;
	return (new);
}
