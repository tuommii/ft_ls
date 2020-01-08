/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:55:37 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/08 18:32:43 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <time.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <sys/ioctl.h>
# include "../libft/includes/libft.h"

# define DAY 86400
# define MAX_PATH 1024
# define ILLEGAL "illegal option -- "
# define USAGE "usage: ft_ls [-lrRat] [file ...]"

# ifndef TIOCGSIZE
#  define TIOCGSIZE TIOCGWINSZ
# endif

typedef struct	s_layout
{
	int			nlink;
	int			user;
	int			group;
	int			size;
	int			name;
	int			blocks;
	int			columns;
	int			code;
}				t_layout;

typedef enum	e_flags
{
	LIST = 1,
	RECURSIVE = 2,
	ALL = 4,
	REVERSE = 8,
	TIME = 16,
	MULTIPLE = 32
}				t_flags;

int				is_dir(struct stat info);
int				is_existing(char *name);
int				is_symlink(char *path, char *name, mode_t mode);

void			ls_swap(t_list *a, t_list *b);
int				is_short_option(char *arg);
void			update_flag(char *str, unsigned int *flags);
int				parse_options(int argc, char **argv, unsigned int *flags);
void			print_options(int flags);

int				print_entries(t_list *list, unsigned int flags,\
				char *path, t_layout *layout);
void			print_details(char *path, char *entry, t_layout *layout);
void			print_permissions(mode_t mode);
void			print_type(mode_t mode);
void			reset_column(int *i, t_layout *layout);

int				scan_folder(char *parent_dir, \
				char *dir_name, unsigned int flags, int code);
int				handle_recursive(t_list *list,\
				char *path, unsigned int flags, t_layout *layout);

t_list			*lst_sort_ascii(t_list *list);
t_list			*sort_time(t_list *list, char *path);

char			*ft_pathjoin(char *path, char *filename);
void			free_list(t_list *node);

void			ls_print_time(time_t mtime);

void			reset_color(void);
void			set_color(mode_t mode);
void			ls_stat_and_colorize(char *full_path,\
				char *filename, int padding, t_layout *layout);
void			err_msg(char *prefix, char *filename);

t_list			*ls_prepare_layout(t_list *list,\
				t_layout *layout, char *path);
t_list			*ls_sort_and_prepare(t_list *list, unsigned int flags,\
				char *dirname, int *code);

#endif
