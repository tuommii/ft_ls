/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 09:43:33 by mtuomine          #+#    #+#             */
/*   Updated: 2019/11/18 09:28:56 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_cut_left(char *str, int n)
{
	int		len;
	int		i;
	char	*new;

	len = ft_strlen(str);
	if (n >= len)
		return ("");
	if (!(new = ft_memalloc(len - n + 1)))
		return (NULL);
	i = 0;
	while (i < n)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
