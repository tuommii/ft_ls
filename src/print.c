/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 09:31:50 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/08 18:03:33 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	handle_content(int *i, t_layout *layout, \
t_list *list, char *path)
{
	char *fullpath;

	if (list->content)
	{
		reset_column(i, layout);
		fullpath = ft_pathjoin(path, list->content);
		ls_stat_and_colorize(fullpath, list->content, layout->name, layout);
		ft_strdel(&fullpath);
	}
}

static void	newline_at_end(unsigned int flags, t_layout *layout)
{
	if (flags & RECURSIVE && !(flags & LIST) && !layout->code)
		ft_printf("\n");
	if (!(flags & RECURSIVE) && !(flags & LIST))
		ft_printf("\n");
}

static void	printing_at_top(unsigned int flags, \
t_layout *layout, char *path, int called)
{
	if ((flags & MULTIPLE && !(flags & RECURSIVE))\
	|| ((flags & RECURSIVE) && (flags & LIST)))
	{
		if (called)
			ft_printf("\n");
		ft_printf("%s:\n", path);
	}
	if (flags & LIST)
		ft_printf("total: %d\n", layout->blocks);
}

int			print_entries(t_list *list, unsigned int flags,\
char *path, t_layout *layout)
{
	static int		called = 0;
	t_list			*begin;
	int				i;

	if (list == NULL || list->content == NULL)
		return (0);
	begin = list;
	printing_at_top(flags, layout, path, called);
	called = 1;
	i = 0;
	while (list)
	{
		(flags & LIST) ? print_details(path, list->content, layout)\
		: handle_content(&i, layout, list, path);
		i++;
		list = list->next;
	}
	newline_at_end(flags, layout);
	list = begin;
	if (flags & RECURSIVE)
		handle_recursive(list, path, flags, layout);
	return (layout->code);
}

void		print_details(char *path, char *entry, t_layout *layout)
{
	struct stat		sb;
	struct passwd	*pwd;
	struct group	*grp;
	char			*str;

	str = ft_pathjoin(path, entry);
	ft_bzero(&sb, sizeof(sb));
	if (lstat(str, &sb) == -1)
		perror("");
	if (!(pwd = getpwuid(sb.st_uid)))
		return ;
	if (!(grp = getgrgid(sb.st_gid)))
		return ;
	print_type(sb.st_mode);
	ft_printf(" %*d", layout->nlink, sb.st_nlink);
	ft_printf(" %*s", layout->user, pwd->pw_name);
	ft_printf(" %*s", layout->group, grp->gr_name);
	ft_printf(" %*ld ", layout->size, sb.st_size);
	ls_print_time(sb.st_mtime);
	set_color(sb.st_mode);
	if (!is_symlink(path, entry, sb.st_mode))
		ft_printf("%s\n", entry);
	reset_color();
	ft_strdel(&str);
}
