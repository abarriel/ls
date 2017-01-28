/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 19:07:10 by abarriel          #+#    #+#             */
/*   Updated: 2017/01/23 15:33:26 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

long	ft_maxi(long s1, long s2)
{
	if (s1 > s2)
		return (s1);
	return (s2);
}

void	width_print_(t_width *w)
{
	w->w_size = ft_pow(w->w_size);
	if (w->w_size <= 1)
		w->w_size = 3;
	else
		w->w_size += 2;
	w->w_nlink = ft_pow(w->w_nlink);
}

t_width	*width_print(t_info *d, t_arg *f)
{
	t_info		*tmp;
	t_width		*w;

	tmp = d;
	w = (t_width*)malloc(sizeof(t_width));
	if (!(f->o & FLAG_A))
		while (ft_strncmp(tmp->name, ".", 1) == 0 && tmp->next)
			tmp = tmp->next;
	w->w_uid = ft_strlen(tmp->uid);
	w->w_gid = ft_strlen(tmp->gid);
	w->w_size = tmp->size;
	w->w_nlink = tmp->nlink;
	while (tmp->next)
	{
		w->w_size = ft_maxi(w->w_size, tmp->next->size);
		w->w_uid = ft_maxi(w->w_uid, ft_strlen(tmp->next->uid));
		w->w_gid = ft_maxi(w->w_gid, ft_strlen(tmp->next->gid));
		w->w_nlink = ft_maxi(w->w_nlink, tmp->next->nlink);
		tmp = tmp->next;
	}
	width_print_(w);
	return (w);
}

void	get_dir_(t_info **dir, t_arg *f)
{
	t_info	*di;
	char	*tmp;

	di = *dir;
	while (di)
	{
		f->path = ft_strjoin(di->name, "/");
		f->rep = opendir(f->path);
		while (f->rep == NULL)
		{
			if (!di->next)
				return ;
			di = di->next;
			f->path = ft_strjoin(di->name, "/");
			f->rep = opendir(f->path);
		}
		while ((f->read_d = readdir(f->rep)) != NULL)
		{
			tmp = ft_strjoin(f->path, f->read_d->d_name);
			lstat(tmp, &f->sb) == -1 ? perror(tmp) : 0;
			add_back(&di->inside, f->read_d->d_name, f);
		}
		sort_dir(&di, f);
		di = di->next;
	}
}

void	get_(t_info **dir, t_info **fich, t_info **err, t_arg *f)
{
	if (lstat(f->ac[f->i], &f->sb) == -1)
	{
		add_back(err, f->ac[f->i], f);
		f->i += 1;
	}
	else if (stat(f->ac[f->i], &f->sb) != -1)
	{
		if ((f->sb.st_mode & S_IFMT) == S_IFDIR)
			add_back(dir, f->ac[f->i], f);
		else
			add_back(fich, f->ac[f->i], f);
		f->i += 1;
	}
	else
	{
		if ((f->sb.st_mode & S_IFMT) == S_IFDIR)
			add_back(dir, f->ac[f->i], f);
		else
			add_back(fich, f->ac[f->i], f);
		f->i += 1;
	}
	f->cas += 1;
}
