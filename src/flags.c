/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 16:43:52 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/08 18:35:22 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	is_short_option(char *arg)
{
	if (!arg)
		return (0);
	if (arg[0] == '-' && arg[1] && arg[1] != '-')
		return (1);
	return (0);
}

int	is_long_option(char *arg)
{
	if (!arg)
		return (0);
	if (ft_strlen(arg) < 3)
		return (0);
	if (arg[0] == '-' && arg[1] && arg[1] == '-')
		return (1);
	return (0);
}

int	update_flag_short(char *str, unsigned int *flags)
{
	while (*++str)
	{
		if (*str == 'l')
			*flags = *flags | LIST;
		else if (*str == 'R')
			*flags = *flags | RECURSIVE;
		else if (*str == 'a')
			*flags = *flags | ALL;
		else if (*str == 'r')
			*flags = *flags | REVERSE;
		else if (*str == 't')
			*flags = *flags | TIME;
		else
			return (1);
	}
	return (0);
}

int	update_flag_long(char *str, unsigned int *flags)
{
	if (ft_strcmp(str, "--list") == 0)
		*flags = *flags | LIST;
	else if (ft_strcmp(str, "--recursive") == 0)
		*flags = *flags | RECURSIVE;
	else if (ft_strcmp(str, "--all") == 0)
		*flags = *flags | ALL;
	else if (ft_strcmp(str, "--reverse") == 0)
		*flags = *flags | REVERSE;
	else if (ft_strcmp(str, "--time") == 0)
		*flags = *flags | TIME;
	else
		return (1);
	return (0);
}

int	parse_options(int argc, char **argv, unsigned int *flags)
{
	int i;

	i = 0;
	while (++i < argc)
	{
		if (is_short_option(argv[i]))
		{
			if (update_flag_short(argv[i], flags))
			{
				ft_printf("%s%s\n%s\n", ILLEGAL, argv[i], USAGE);
				exit(1);
			}
		}
		else if (is_long_option(argv[i]))
		{
			if (update_flag_long(argv[i], flags))
			{
				ft_printf("%s%s\n%s\n", ILLEGAL, argv[i], USAGE);
				exit(1);
			}
		}
		else if (argv[i][0] != '-')
			return (i);
	}
	return (i);
}
