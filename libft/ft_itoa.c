/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:43:14 by mtuomine          #+#    #+#             */
/*   Updated: 2019/10/17 11:29:27 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			len(int n)
{
	int len;

	len = 1;
	while (n /= 10)
		len++;
	return (len);
}

char				*ft_itoa(int n)
{
	char	*str;
	int		size;
	int		sign;

	sign = 0;
	str = NULL;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		sign = 1;
	size = len(n);
	if (!(str = ft_strnew(size + sign)))
		return (NULL);
	if (sign)
		str[0] = '-';
	while (size--)
	{
		if (sign)
			str[size + sign] = -n % 10 + '0';
		else
			str[size + sign] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
