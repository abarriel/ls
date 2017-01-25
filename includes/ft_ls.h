/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 23:48:34 by abarriel          #+#    #+#             */
/*   Updated: 2017/01/25 16:38:16 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include "ft_printf.h"
# include <stdio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# define FLAG_LR 1
# define FLAG_L 2
# define FLAG_A 4
# define FLAG_UR 8
# define FLAG_T 16

typedef struct	s_info
{
	char			*path;
	char			*name;
	char			type;
	char			*mode;
	int				nlink;
	char			*uid;
	char			*gid;
	long			size;
	char			*mtime_;
	long			blocks;
	int				major;
	int				minor;
	struct timespec	mtime;
	struct timespec	mtime_sec;
	struct s_info	*inside;
	struct s_info	*next;
}				t_info;
typedef struct	s_width
{
	int				w_uid;
	long			w_size;
	int				w_gid;
	long			w_nlink;
}				t_width;

typedef struct	s_arg
{
	char			*path;
	char			*tmp;
	char			*name;
	char			*p_tmp;
	int				i_tmp;
	int				cas;
	int				dede;
	int				o;
	int				no_opt;
	int				av;
	int				i;
	DIR				*rep;
	struct stat		sb;
	char			**ac;
	struct dirent	*read_d;
}				t_arg;
char			get_eight(struct stat sb);
char			get_five(struct stat sb);
char			get_nine(struct stat sb);
void			ft_list_reverse(t_info **begin_list);
long			ft_maxi(long s1, long s2);
long			ft_pow(long s1);
void			print_long(t_info *d, t_width *w);
void			ft_list_swap(t_info **current);
void			check_arg(t_arg *f, char *ac);
void			sort_dir(t_info **di, t_arg *f);
void			lstdel(t_info **alst);
void			lstdelone(t_info **alst);
void			lstdel_d(t_info **alst);
void			lstdelone_d(t_info **alst);
void			print_info(t_info *d, t_arg *f, t_width *w);
void			add_back(t_info **s, char *ac, t_arg *f);
void			sort_ascii(t_info **begin_list);
void			sort_ascii_r(t_info **begin_list);
void			sort_r(t_info **begin_list);
t_info			*get_info(t_arg *f);
int				print_av_null(t_arg *f);
t_info			*set_info(void);
void			reversesort(t_info **list);
void			get_blocks_size(t_info *dir, t_arg *f);
t_width			*width_print(t_info *d, t_arg *f);
void			sort_re(t_info *di, t_arg *f);
void			recur_(t_info *di, t_arg *f);
void			get_(t_info **dir, t_info **fich, t_info **err, t_arg *f);
void			sort_(t_info **dir, t_info **fich, t_arg *f);
void			sort_recur(t_info **dir, t_arg *f);
void			print_(t_info *err, t_info *fich, t_arg *f);
void			get_dir_(t_info **dir, t_arg *f);
void			sort_time(t_info **begin_list);
void			sort_time_r(t_info **begin_list);
t_info			*get_name(char *ac, t_arg *f);
void			print_dir(t_info *dir, t_arg *f);
#endif
