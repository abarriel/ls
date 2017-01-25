/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_long_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 20:44:57 by abarriel          #+#    #+#             */
/*   Updated: 2017/01/23 15:47:28 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_mode(struct stat sb)
{
	char *str;

	str = ft_strnew(10);
	str[0] = (sb.st_mode & S_IRUSR) ? 'r' : '-';
	str[1] = (sb.st_mode & S_IWUSR) ? 'w' : '-';
	str[2] = get_nine(sb);
	str[3] = (sb.st_mode & S_IRGRP) ? 'r' : '-';
	str[4] = (sb.st_mode & S_IWGRP) ? 'w' : '-';
	str[5] = get_five(sb);
	str[6] = (sb.st_mode & S_IROTH) ? 'r' : '-';
	str[7] = (sb.st_mode & S_IWOTH) ? 'w' : '-';
	str[8] = get_eight(sb);
	return (str);
}

char	get_type(struct stat sb)
{
	if ((sb.st_mode & S_IFMT) == S_IFREG)
		return ('-');
	if ((sb.st_mode & S_IFMT) == S_IFDIR)
		return ('d');
	if ((sb.st_mode & S_IFMT) == S_IFIFO)
		return ('p');
	if ((sb.st_mode & S_IFMT) == S_IFLNK)
		return ('l');
	if (S_ISCHR(sb.st_mode))
		return ('c');
	if (S_ISBLK(sb.st_mode))
		return ('b');
	if ((sb.st_mode & S_IFMT) == S_IFSOCK)
		return ('s');
	return ('?');
}

char	*get_time(time_t mtime)
{
	char		*mtime_n;
	char		*time_;
	char		*tmp;
	time_t		t;

	t = time(0);
	mtime_n = ctime(&mtime);
	if (mtime > t || t - mtime > 15778458)
	{
		time_ = ctime(&mtime);
		tmp = time_;
		tmp = ft_strsub(tmp, 20, 4);
		time_ = ft_strsub(time_, 4, 7);
		time_ = ft_strjoin_three(time_, " ", tmp);
	}
	else
		time_ = ft_strsub(ctime(&mtime), 4, 12);
	return (time_);
}

void	get_name_(t_info *tmp, t_arg *f)
{
	tmp->size = f->sb.st_size;
	tmp->mode = get_mode(f->sb);
	tmp->blocks = f->sb.st_blocks;
	tmp->mtime = f->sb.st_mtimespec;
	tmp->mtime_ = get_time(tmp->mtime.tv_sec);
	tmp->inside = NULL;
	tmp->next = NULL;
}

t_info	*get_name(char *ac, t_arg *f)
{
	t_info	*tmp;

	tmp = (t_info*)malloc(sizeof(t_info));
	tmp->name = ft_strdup(ac);
	tmp->nlink = f->sb.st_nlink;
	tmp->type = get_type(f->sb);
	if (getpwuid(f->sb.st_uid) == NULL)
		tmp->uid = ft_strdup("root");
	else
		tmp->uid = getpwuid(f->sb.st_uid)->pw_name;
	if (getgrgid(f->sb.st_gid) == NULL)
		tmp->gid = ft_strdup("wheel");
	else
		tmp->gid = getgrgid(f->sb.st_gid)->gr_name;
	tmp->path = f->path;
	if ((tmp->type == 'b') || (tmp->type == 'c'))
	{
		tmp->major = (int)major(f->sb.st_rdev);
		tmp->minor = (int)minor(f->sb.st_rdev);
	}
	get_name_(tmp, f);
	return (tmp);
}
