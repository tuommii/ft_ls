/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:59:10 by mtuomine          #+#    #+#             */
/*   Updated: 2019/10/17 07:42:09 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	sc(char const *s, char c)
{
	int	strings;
	int i;

	i = 0;
	strings = 0;
	while (s[i])
	{
		if (s[i] == c && (s[i + 1] != c && s[i + 1] != '\0'))
			strings++;
		i++;
	}
	if (s[0] != '\0')
		strings++;
	return (strings);
}

static int	cc(char const *s, char c)
{
	int count;

	count = 0;
	while (*s)
	{
		if (*s != c)
			count++;
		s++;
	}
	return (count);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	char	**a;

	i = 0;
	j = 0;
	if (!s || !c || (!(a = (char **)malloc(sizeof(char *) * sc(s, c) + 1))))
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			if (!s || (!(a[i] = (char *)malloc(sizeof(char) * cc(s, c) + 1))))
				return (NULL);
			while (*s != c && *s)
				a[i][j++] = (char)*s++;
			a[i][j] = '\0';
			i++;
			j = 0;
		}
	}
	a[i] = NULL;
	return (a);
}
