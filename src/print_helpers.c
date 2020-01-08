/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 16:32:23 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/08 17:13:35 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_permissions(mode_t mode)
{
	ft_printf("%c", (mode & S_IRUSR) ? 'r' : '-');
	ft_printf("%c", (mode & S_IWUSR) ? 'w' : '-');
	ft_printf("%c", (mode & S_IXUSR) ? 'x' : '-');
	ft_printf("%c", (mode & S_IRGRP) ? 'r' : '-');
	ft_printf("%c", (mode & S_IWGRP) ? 'w' : '-');
	ft_printf("%c", (mode & S_IXGRP) ? 'x' : '-');
	ft_printf("%c", (mode & S_IROTH) ? 'r' : '-');
	ft_printf("%c", (mode & S_IWOTH) ? 'w' : '-');
	ft_printf("%c", (mode & S_IXOTH) ? 'x' : '-');
}

void	print_type(mode_t mode)
{
	if (S_ISREG(mode))
		ft_printf("%c", '-');
	else if (S_ISDIR(mode))
		ft_printf("%c", 'd');
	else if (S_ISLNK(mode))
		ft_printf("%c", 'l');
	else if (S_ISSOCK(mode))
		ft_printf("%c", 's');
	else if (S_ISCHR(mode))
		ft_printf("%c", 'c');
	else if (S_ISBLK(mode))
		ft_printf("%c", 'b');
	else if (S_ISFIFO(mode))
		ft_printf("%c", 'f');
	print_permissions(mode);
}

void	reset_column(int *i, t_layout *layout)
{
	if (*i == layout->columns)
	{
		ft_printf("\n");
		*i = 0;
	}
}
