/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:54:53 by mtuomine          #+#    #+#             */
/*   Updated: 2019/10/17 10:56:33 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	len;
	size_t	i;
	char	*fresh;

	if (!s || !f)
		return (NULL);
	len = ft_strlen((char *)s);
	if (!(fresh = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		fresh[i] = (*f)((char)s[i]);
		i++;
	}
	fresh[len] = '\0';
	return (fresh);
}
