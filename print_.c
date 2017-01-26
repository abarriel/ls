/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 11:43:31 by abarriel          #+#    #+#             */
/*   Updated: 2017/01/23 16:09:50 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_long(t_info *d, t_width *w)
{
	if (d->type)
		ft_printf("%c", d->type);
	if (d->mode)
		ft_printf("%s ", d->mode);
	ft_printf("%*d ", w->w_nlink + 1, d->nlink);
	if (d->uid)
		ft_printf("%-*s ", w->w_uid + 1, d->uid);
	if (d->gid)
		ft_printf("%-*s", w->w_gid, d->gid);
	if ((d->type == 'b') || (d->type == 'c'))
	{
		ft_printf("%*d, ", 3, d->major);
		ft_printf("%*d ", 3, d->minor);
		w->w_size = 6;
	}
	else
		ft_printf("%*ld ", w->w_size + 2, d->size);
	if (d->mtime_)
		ft_printf("%s ", d->mtime_);
}

void	print_info(t_info *d, t_arg *f, t_width *w)
{
	char	buf[257];
	int		i;

	i = 0;
	if (!d)
		return ;
	if (f->o & FLAG_L)
		print_long(d, w);
	if (d->type == 'l')
	{
		ft_printf("%s", d->name);
		if (f->o & FLAG_L)
		{
			if ((i = readlink(ft_strjoin(d->path, d->name), buf,
							sizeof(buf) - 1)) != -1)
				buf[i] = '\0';
			ft_printf(" -> %s\n", buf);
		}
		else
			ft_printf("\n");
	}
	else
		ft_printf("%s\n", d->name);
}

void	print_dir_(t_arg *f, t_info *tmp, t_width *w)
{
	if (tmp && tmp->inside)
		w = width_print(tmp->inside, f);
	while (tmp->inside)
	{
		if ((f->o & FLAG_A))
			print_info(tmp->inside, f, w);
		else if (ft_strncmp(tmp->inside->name, ".", 1) != 0)
			print_info(tmp->inside, f, w);
		tmp->inside = tmp->inside->next;
	}
}

void	print_dir(t_info *dir, t_arg *f)
{
	t_info	*tmp;
	t_width	*w;

	tmp = dir;
	w = NULL;
	while (tmp)
	{
		if (f->o & FLAG_L)
			get_blocks_size(tmp, f);
		else
		{
			if (f->cas != 1)
				ft_printf("%s:\n", tmp->name);
		}
		if (!tmp->inside)
		{
			ft_printf("ls: ");
			perror(tmp->name);
		}
		print_dir_(f, tmp, w);
		if (tmp->next)
			ft_printf("\n");
		tmp = tmp->next;
	}
}

void	print_(t_info *err, t_info *fich, t_arg *f)
{
	t_width	*w;

	while (err)
	{
		ft_printf("ls: %s: No such file or directory\n", err->name);
		err = err->next;
	}
	if (fich)
		w = width_print(fich, f);
	while (fich)
	{
		if ((f->o & FLAG_A))
			print_info(fich, f, w);
		else if (ft_strncmp(fich->name, ".", 1) != 0)
			print_info(fich, f, w);
		fich = fich->next;
	}
	f->i_tmp = 4;
}
