/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 08:31:04 by mtuomine          #+#    #+#             */
/*   Updated: 2019/10/16 10:54:03 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *ps1;
	unsigned char *ps2;

	while (n > 0)
	{
		ps1 = (unsigned char *)s1;
		ps2 = (unsigned char *)s2;
		if (*ps1 != *ps2)
			return (*ps1 - *ps2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
