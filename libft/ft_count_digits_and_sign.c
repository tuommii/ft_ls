/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits_and_sign.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 09:19:06 by mtuomine          #+#    #+#             */
/*   Updated: 2019/11/16 09:38:37 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_digits_and_sign(intmax_t n, int base)
{
	int count;

	count = ft_count_digits_only((uintmax_t)n, base);
	if (n < 0)
		count++;
	return (count);
}
