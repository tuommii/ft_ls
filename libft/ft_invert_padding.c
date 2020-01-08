/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_invert_padding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 09:05:56 by mtuomine          #+#    #+#             */
/*   Updated: 2019/11/28 10:48:01 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	create_inv(char *dest, char *src, int right_pad, int num_size)
{
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = ft_strlen(dest);
	while (i < len)
	{
		if (i < right_pad)
			dest[i] = ' ';
		if (i >= right_pad && i < (right_pad + num_size))
		{
			dest[i] = src[j];
			j++;
		}
		i++;
	}
	dest[len] = '\0';
}

char		*ft_invert_padding(char *str, int len)
{
	char	*temp;
	char	num[len + 1];
	int		i;
	int		k;
	int		left_pad;

	temp = ft_strnew(len);
	i = 0;
	k = 0;
	left_pad = 0;
	ft_memset(temp, ' ', len);
	while (str[i] && ft_isspace(str[i]))
		i++;
	left_pad = i;
	while ((str[i] && !ft_isspace(str[i])))
	{
		temp[k] = str[i];
		num[k] = str[i];
		i++;
		k++;
	}
	create_inv(temp, num, len - ((i - left_pad) + left_pad), i - left_pad);
	return (temp);
}
