/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 14:46:47 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/08 16:27:36 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*ft_pathjoin(char *path, char *filename)
{
	char	*res;
	char	*cpy;
	int		i;

	i = 0;
	cpy = (char *)path;
	if (!path && ft_strequ(filename, "."))
		return (ft_strdup("./"));
	else if (ft_strequ(path, filename))
		return (ft_strjoin(filename, "/"));
	else if (ft_strequ(path, "./") && filename[0] == '/')
		return (ft_strdup(filename));
	else if (!path && filename)
		return (ft_strdup(filename));
	if (!(res = ft_memalloc(sizeof(*res) * (ft_strlen(path) +\
	ft_strlen(filename) + 2))))
		res = ft_strnew(1);
	while (*path)
		res[i++] = *path++;
	if (res[i - 1] != '/' && !ft_strequ(cpy, "./") && filename[0] != '\0')
		res[i++] = '/';
	while (*filename)
		res[i++] = *filename++;
	res[i] = '\0';
	return (res);
}

static void	free_node(t_list *node)
{
	ft_memdel((void **)&node);
}

void		free_list(t_list *list)
{
	if (list)
		ft_lstdel(&list, (void *)free_node);
}

void		ls_swap(t_list *a, t_list *b)
{
	void *temp;

	temp = a->content;
	a->content = b->content;
	b->content = temp;
}
