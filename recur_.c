/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recur_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 13:14:57 by abarriel          #+#    #+#             */
/*   Updated: 2017/01/23 15:25:48 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_re(t_info *new, t_arg *f)
{
	t_info	*tmp;
	t_width	*w;

	tmp = new;
	if (tmp && (f->o & FLAG_L))
		w = width_print(tmp, f);
	while (tmp)
	{
		if ((f->o & FLAG_A))
			print_info(tmp, f, w);
		else if (ft_strncmp(tmp->name, ".", 1) != 0)
			print_info(tmp, f, w);
		tmp = tmp->next;
	}
}

void	recur_1(t_info *di, t_arg *f)
{
	t_info	*new;

	new = NULL;
	f->rep = opendir(f->path);
	ft_printf("\n%s:\n", f->name);
	if (f->rep == NULL)
	{
		ft_printf("ls: ");
		perror(di->name);
		return ;
	}
	while ((f->read_d = readdir(f->rep)) != NULL)
	{
		f->p_tmp = ft_strjoin(f->path, f->read_d->d_name);
		if (lstat(f->p_tmp, &f->sb) == -1)
			perror(f->p_tmp);
		add_back(&new, f->read_d->d_name, f);
	}
	closedir(f->rep);
	sort_recur(&new, f);
	if (f->o & FLAG_L)
		get_blocks_size(new, f);
	print_re(new, f);
	recur_(new, f);
}

void	recur_(t_info *di, t_arg *f)
{
	while (di)
	{
		if (di->type == 'd' && (!(f->o & FLAG_A) &&
					ft_strncmp(di->name, ".", 1) == 0))
		{
			f->path = di->path;
			di = di->next;
		}
		else
		{
			if (di->type == 'd' && ft_strcmp(di->name, ".") != 0
					&& ft_strncmp(di->name, "..", 2) != 0)
			{
				f->name = ft_strjoin(f->path, di->name);
				f->path = ft_strjoin_three(f->path, di->name, "/");
				recur_1(di, f);
			}
			f->path = di->path;
			di = di->next;
		}
	}
}
