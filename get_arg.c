/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 20:24:23 by abarriel          #+#    #+#             */
/*   Updated: 2017/01/23 18:36:46 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_stop(char *ac)
{
	if (*ac && ac)
	{
		ft_putstr_fd("ls: illegal option -- ", 2);
		ft_putstr_fd(ac, 2);
		ft_putstr_fd("\nusage: ls [-Ra1ltr] [file ...]\n", 2);
	}
	exit(1);
}

void	get_opt_(t_arg *f, char *ac, int i)
{
	if (ac[i] == '-' && (f->o == 0))
		ft_stop(ac);
	else if (ac[i] == 'l')
		f->o = f->o | FLAG_L;
	else if (ac[i] == 'a')
		f->o = f->o | FLAG_A;
	else if (ac[i] == 'r')
		f->o = f->o | FLAG_LR;
	else if (ac[i] == 'R')
		f->o = f->o | FLAG_UR;
	else if (ac[i] == 't')
		f->o = f->o | FLAG_T;
	else if (ac[i] != '1')
		ft_stop(ac);
}

int		get_opt(t_arg *f, char *ac)
{
	int i;

	i = 1;
	if (ac[i] == '-' && f->no_opt == 0)
	{
		if (ac[i + 1] != ' ' && ft_strcmp(ac, "--") != 0)
			ft_stop(ac);
		return (f->no_opt = f->no_opt | 1);
	}
	while (ac[i])
	{
		get_opt_(f, ac, i);
		i++;
	}
	return (0);
}

void	check_arg(t_arg *f, char *ac)
{
	int i;

	i = 0;
	while (ac[i])
	{
		if (f->no_opt == 0)
		{
			if ((ac[i] == '-' && !ac[i + 1]) || ac[i] != '-')
			{
				f->no_opt = f->no_opt | 1;
				f->i -= 1;
				break ;
			}
		}
		if (ac[i] == '-')
		{
			get_opt(f, ac);
			break ;
		}
		i++;
	}
}
