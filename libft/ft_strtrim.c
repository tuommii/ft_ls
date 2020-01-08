/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:39:49 by mtuomine          #+#    #+#             */
/*   Updated: 2019/10/16 13:57:20 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace2(char c)
{
	if (c == '\t' || c == '\n' || c == ' ')
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	char	*res;
	size_t	i;
	size_t	end;

	if (!s)
		return (NULL);
	i = 0;
	while (ft_isspace2(s[i]))
		i++;
	end = ft_strlen(s);
	while (i < end && ft_isspace2(s[end - 1]))
		end--;
	if (i == end)
		return (ft_strnew(1));
	res = ft_strsub(s, i, (end - i));
	return (res);
}
