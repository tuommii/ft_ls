/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 09:23:26 by mtuomine          #+#    #+#             */
/*   Updated: 2019/11/18 09:26:10 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_uitoa_base(uintmax_t n, unsigned int base, \
const char *symbols, size_t precision)
{
	size_t	count;
	char	*str;

	count = ft_count_digits_only(n, base);
	if (count < precision)
		count = precision;
	if (!(str = ft_memalloc(count + 1)))
		return (NULL);
	while (count > 0)
	{
		str[count - 1] = symbols[n % base];
		count--;
		n /= base;
	}
	return (str);
}
