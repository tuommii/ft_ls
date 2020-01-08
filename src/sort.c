/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:03:06 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/08 16:29:34 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list		*lst_sort_ascii(t_list *list)
{
	void	*swap;
	t_list	*begin;

	begin = list;
	while (list && list->next)
	{
		if (ft_strcmp(list->content, list->next->content) > 0)
		{
			swap = list->content;
			list->content = list->next->content;
			list->next->content = swap;
			list = begin;
		}
		else
		{
			list = list->next;
		}
	}
	list = begin;
	return (list);
}

static int	compare_times(struct stat *sb, struct stat *sb2)
{
	time_t a;
	time_t b;

	a = sb->st_mtime;
	b = sb2->st_mtime;
	if (a > b)
		return (-1);
	else if (a < b)
		return (1);
	return (0);
}

static void	compare_result(int res, t_list *node, t_list *node2)
{
	if (res > 0)
		ls_swap(node, node2);
	else if (res == 0)
	{
		if (ft_strcmp(node->content, node2->content) > 0)
		{
			ls_swap(node, node2);
		}
	}
}

static void	stat_file(struct stat *sb, char *path, char *filename)
{
	char *str;

	str = ft_pathjoin(path, filename);
	lstat(str, sb);
	ft_strdel(&str);
}

t_list		*sort_time(t_list *list, char *path)
{
	t_list		*begin;
	t_list		*temp;
	struct stat	sb;
	struct stat	sb2;

	begin = list;
	while (list)
	{
		temp = list->next;
		while (temp)
		{
			stat_file(&sb, path, list->content);
			stat_file(&sb2, path, temp->content);
			compare_result(compare_times(&sb, &sb2), list, temp);
			temp = temp->next;
		}
		list = list->next;
	}
	list = begin;
	return (list);
}
