/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 12:30:39 by abarriel          #+#    #+#             */
/*   Updated: 2017/01/23 16:33:49 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

t_arg	*set_arg(int av, char **ac)
{
	t_arg	*f;

	if (!(f = (t_arg *)malloc(sizeof(t_arg))))
		return (0);
	f->i = 1;
	f->i_tmp = 0;
	f->cas = 0;
	f->av = av;
	f->path = "./";
	f->tmp = NULL;
	f->name = NULL;
	f->p_tmp = NULL;
	f->no_opt = 0;
	f->o = 0;
	f->ac = ac;
	return (f);
}

int		main_(t_arg *f, t_info *dir)
{
	t_info	*new;

	if (f->av == -1 && dir && !(f->o & FLAG_UR))
	{
		ft_printf("\n");
		f->i_tmp = 0;
	}
	print_dir(dir, f);
	if (dir)
		get_dir_(&dir, f);
	while ((f->o & FLAG_UR) && dir)
	{
		new = dir->inside;
		recur_(new, f);
		if (dir->next)
			dir = dir->next;
		else
			return (0);
	}
	return (0);
}

int		main(int av, char **ac)
{
	t_arg	*f;
	t_info	*err;
	t_info	*fich;
	t_info	*dir;

	f = set_arg(av, ac);
	while (f && f->i < av && !(f->no_opt & 3))
		check_arg(f, ac[f->i++]);
	if (f && f->i == av)
	{
		f->ac[f->i] = ft_strdup(".");
		av++;
	}
	f->i_tmp = f->i;
	while (f->i_tmp++ < av)
		get_(&dir, &fich, &err, f);
	sort_ascii(&err);
	sort_(&dir, &fich, f);
	if (fich)
		f->av = -1;
	if (dir)
		get_dir_(&dir, f);
	print_(err, fich, f);
	main_(f, dir);
	return (0);
}
