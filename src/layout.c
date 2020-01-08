/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 09:25:31 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/08 17:59:40 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	count_digits(unsigned int n)
{
	unsigned int count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		++count;
		n /= 10;
	}
	return (count);
}

static void	set_maximums(t_layout *layout, struct stat sb)
{
	struct passwd	*pwd;
	struct group	*grp;
	unsigned int	nums_size;
	unsigned int	nums_nlink;

	nums_size = count_digits(sb.st_size);
	nums_nlink = count_digits(sb.st_nlink);
	if (!(pwd = getpwuid(sb.st_uid)))
		return ;
	if (!(grp = getgrgid(sb.st_gid)))
		return ;
	if (ft_strlen(pwd->pw_name) > (size_t)layout->user)
		layout->user = ft_strlen(pwd->pw_name);
	if (ft_strlen(grp->gr_name) > (size_t)layout->group)
		layout->group = ft_strlen(grp->gr_name);
	if (nums_size > (size_t)layout->size)
		layout->size = nums_size;
	if (nums_nlink > (size_t)layout->nlink)
		layout->nlink = nums_nlink;
	layout->blocks = layout->blocks + sb.st_blocks;
}

static void	set_layout(t_layout *layout, char *path, char *filename)
{
	struct stat	sb;
	char		*str;

	str = ft_pathjoin(path, filename);
	if (lstat(str, &sb) == -1)
	{
		layout->code = 1;
	}
	set_maximums(layout, sb);
	ft_strdel(&str);
}

t_list		*ls_sort_and_prepare(t_list *list,\
unsigned int flags, char *dirname, int *code)
{
	t_layout	layout;

	layout.name = 1;
	layout.group = 1;
	layout.nlink = 1;
	layout.size = 1;
	layout.user = 1;
	layout.blocks = 0;
	layout.columns = 1;
	layout.code = 0;
	list = ls_prepare_layout(list, &layout, dirname);
	if (!(flags & TIME))
		list = lst_sort_ascii(list);
	if (flags & TIME)
		list = sort_time(list, dirname);
	if (flags & REVERSE)
		list = ft_lstreverse(list);
	print_entries(list, flags, dirname, &layout);
	if (layout.code > *code)
		*code = layout.code;
	return (list);
}

t_list		*ls_prepare_layout(t_list *list, t_layout *layout, char *path)
{
	t_list			*begin;
	struct winsize	w;

	ioctl(0, TIOCGSIZE, &w);
	begin = list;
	while (list)
	{
		if (list->content_size > (size_t)layout->name)
			layout->name = list->content_size;
		set_layout(layout, path, list->content);
		list = list->next;
	}
	list = begin;
	layout->columns = w.ws_col / layout->name;
	return (list);
}
