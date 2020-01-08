/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 12:19:55 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/08 16:25:37 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	is_dir(struct stat info)
{
	if (S_ISDIR(info.st_mode))
		return (1);
	return (0);
}

int	is_symlink(char *path, char *name, mode_t mode)
{
	char buf[MAX_PATH];
	char *fullpath;

	fullpath = ft_pathjoin(path, name);
	ft_memset(buf, 0, MAX_PATH);
	if (!S_ISLNK(mode))
	{
		set_color(mode);
		ft_strdel(&fullpath);
		return (0);
	}
	if (readlink(fullpath, buf, MAX_PATH) != -1)
	{
		ft_printf("%s ", name);
		reset_color();
		buf[MAX_PATH - 1] = '\0';
		ft_printf("-> %s\n", buf);
		ft_strdel(&fullpath);
		return (1);
	}
	ft_strdel(&fullpath);
	return (0);
}

int	is_existing(char *name)
{
	struct stat sb;

	if (lstat(name, &sb) == 0)
		return (1);
	return (0);
}
