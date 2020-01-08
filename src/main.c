/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:55:40 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/08 18:02:41 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	handle_stat_err(struct stat *sb, char *full_path, t_layout *layout)
{
	if (lstat(full_path, sb) == -1)
	{
		layout->code = 1;
		ft_strdel(&full_path);
		return (1);
	}
	return (0);
}

int			handle_recursive(t_list *list, char *path,\
unsigned int flags, t_layout *layout)
{
	static int	called = 0;
	struct stat	sb;
	char		*full_path;

	while (list)
	{
		full_path = ft_pathjoin(path, list->content);
		if (handle_stat_err(&sb, full_path, layout))
			return (1);
		if (is_dir(sb))
		{
			if (!(ft_strequ(list->content, ".") \
			|| ft_strequ(list->content, "..")))
			{
				if (++called >= 1 && !(flags & LIST))
					ft_printf("\n");
				if (!(flags & LIST))
					ft_printf("%s:\n", full_path);
				scan_folder(full_path, full_path, flags, layout->code);
			}
		}
		list = list->next;
		ft_strdel(&full_path);
	}
	return (layout->code);
}

static int	handle_dir_err(DIR **folder, char *full_path)
{
	if (!(*folder = opendir(full_path)))
	{
		if (is_existing(full_path))
			ft_printf("%s\n", full_path);
		else
			err_msg("ft_ls: ", full_path);
		ft_strdel(&full_path);
		return (1);
	}
	return (0);
}

int			scan_folder(char *parent, char *dirname,\
unsigned int flags, int code)
{
	DIR				*folder;
	t_list			*list;
	struct dirent	*entry;
	char			*full_path;
	static int		temp = 0;

	folder = NULL;
	list = NULL;
	if (code > 0)
		temp = 1;
	full_path = ft_pathjoin(parent, dirname);
	if (handle_dir_err(&folder, full_path))
		return (1);
	if (ft_strequ(full_path, "./") && flags & RECURSIVE && !(flags & LIST))
		ft_printf("./:\n");
	while ((entry = readdir(folder)) != NULL)
		if (entry->d_name[0] != '.' || (flags & ALL))
			ft_lstadd(&list, ft_lstnew(entry->d_name,\
			ft_strlen(entry->d_name) + 1));
	closedir(folder);
	list = ls_sort_and_prepare(list, flags, full_path, &temp);
	ft_strdel(&full_path);
	free_list(list);
	return (temp);
}

int			main(int argc, char **argv)
{
	unsigned int	flags;
	int				i;
	int				res;

	i = 0;
	flags = 0;
	res = 0;
	i = parse_options(argc, argv, &flags);
	if ((argc - i) > 1)
		flags = flags | MULTIPLE;
	if (i == argc)
		res = scan_folder(NULL, ".", flags, 0);
	else
	{
		i--;
		while ((i++) < (argc - 1))
		{
			res = scan_folder(NULL, argv[i], flags, 0);
		}
	}
	exit(res);
}
