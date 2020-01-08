/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pad_right.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 09:35:04 by mtuomine          #+#    #+#             */
/*   Updated: 2019/11/16 09:37:57 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_pad_right(char *str, int total_width, char c)
{
	int		i;
	int		len;
	char	*new;

	len = ft_strlen(str);
	if (len >= total_width)
		return (str);
	new = ft_strnew(total_width);
	i = 0;
	while (i < len)
		new[i++] = *str++;
	while (i < total_width)
		new[i++] = c;
	return (new);
}
