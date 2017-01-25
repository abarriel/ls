/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 18:32:42 by abarriel          #+#    #+#             */
/*   Updated: 2017/01/23 15:33:48 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_blocks_size(t_info *dir, t_arg *f)
{
	t_info	*tmp;
	size_t	blocks;

	if (dir->inside)
		tmp = dir->inside;
	else
		tmp = dir;
	blocks = 0;
	while (tmp)
	{
		if ((f->o & FLAG_A))
			blocks += tmp->blocks;
		else if (ft_strncmp(tmp->name, ".", 1) != 0)
			blocks += tmp->blocks;
		tmp = tmp->next;
	}
	if (dir->inside && f->cas != 1)
		ft_printf("%s:\n", dir->name);
	ft_printf("total %d\n", blocks);
}

void	ft_list_swap(t_info **current)
{
	t_info	*tmp;

	tmp = (*current)->next->next;
	(*current)->next->next = (*current);
	(*current)->next = tmp;
}

void	add_back(t_info **s, char *ac, t_arg *f)
{
	t_info *tmp;

	tmp = *s;
	if (!tmp)
	{
		*s = get_name(ac, f);
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = get_name(ac, f);
}

long	ft_pow(long s1)
{
	long	i;

	i = 0;
	while (s1 > 0)
	{
		s1 /= 10;
		i++;
	}
	return (i);
}

void	reversesort(t_info **list)
{
	t_info	*p;
	t_info	*q;
	t_info	*r;

	p = *list;
	q = NULL;
	while (p)
	{
		r = q;
		q = p;
		p = p->next;
		q->next = r;
	}
	*list = q;
}
