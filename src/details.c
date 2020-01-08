/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   details.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:55:15 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/08 18:01:57 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_print_time(time_t mtime)
{
	char	*str;
	time_t	now;
	char	*begin;
	time_t	interval;

	if (!(str = ctime(&mtime)))
		return ;
	now = time(NULL);
	interval = (now - mtime) / DAY;
	str[ft_strlen(str) - 1] = '\0';
	begin = str;
	if (interval >= 364 || interval <= -364)
	{
		str += 4;
		ft_printf("%6.6s", str);
		str += 15;
		ft_printf("%6.5s ", str);
	}
	else
	{
		begin += 4;
		ft_printf("%.12s ", begin);
	}
}

void	set_color(mode_t mode)
{
	if (S_ISDIR(mode))
		ft_printf(FT_BOLD_BLUE);
	else if (S_ISCHR(mode))
		ft_printf(FT_YELLOW);
	else if (S_ISLNK(mode))
		ft_printf(FT_RED);
	if ((mode & S_IXUSR || mode & S_IXGRP || mode & S_IXOTH) \
	&& !S_ISDIR(mode) && !S_ISLNK(mode))
		ft_printf(FT_GREEN);
}

void	reset_color(void)
{
	ft_printf(FT_RESET);
}

void	ls_stat_and_colorize(char *full_path, char *filename,\
int padding, t_layout *layout)
{
	struct stat sb;

	if (lstat(full_path, &sb) == -1)
	{
		layout->code = 1;
		set_color(sb.st_mode);
		ft_printf("%-*s", padding, filename);
		reset_color();
		err_msg("\nft_ls: ", full_path);
		return ;
	}
	set_color(sb.st_mode);
	ft_printf("%-*s", padding, filename);
	reset_color();
}

void	err_msg(char *prefix, char *filename)
{
	char *msg;

	if (!(msg = ft_strjoin(prefix, filename)))
	{
		perror("");
		return ;
	}
	perror(msg);
	ft_strdel(&msg);
}
