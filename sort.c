/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 02:31:51 by abarriel          #+#    #+#             */
/*   Updated: 2017/01/23 16:34:46 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_ascii(t_info **begin_list)
{
	t_info	*current;
	t_info	*last;

	current = *begin_list;
	if (!*begin_list)
		return ;
	while (current->next)
	{
		if (ft_strcmp(current->name, current->next->name) > 0)
		{
			if (current != *begin_list)
				last->next = current->next;
			else
				*begin_list = current->next;
			ft_list_swap(&current);
			current = *begin_list;
		}
		else
		{
			last = current;
			current = current->next ? current->next : current;
		}
	}
}

void	sort_r(t_info **begin_list)
{
	t_info	*current;
	t_info	*last;

	current = *begin_list;
	if (!*begin_list)
		return ;
	while (current->next)
	{
		if (ft_strcmp(current->name, current->next->name) < 0)
		{
			if (current != *begin_list)
				last->next = current->next;
			else
				*begin_list = current->next;
			ft_list_swap(&current);
			current = *begin_list;
		}
		else
		{
			last = current;
			current = current->next ? current->next : current;
		}
	}
}

void	sort_(t_info **dir, t_info **fich, t_arg *f)
{
	if (!(f->o & FLAG_T))
	{
		sort_ascii(dir);
		sort_ascii(fich);
	}
	if (f->o & FLAG_T)
	{
		sort_time(dir);
		sort_time(fich);
	}
	if (f->o & FLAG_LR)
	{
		reversesort(dir);
		reversesort(fich);
	}
}

void	sort_recur(t_info **dir, t_arg *f)
{
	if (f->o & FLAG_T)
		sort_time(dir);
	if (f->o & FLAG_LR)
		reversesort(dir);
}

void	sort_dir(t_info **di, t_arg *f)
{
	if (!(f->o & FLAG_T))
		sort_ascii(&(*di)->inside);
	else if (f->o & FLAG_T)
		sort_time(&(*di)->inside);
	if (f->o & FLAG_LR)
		reversesort(&(*di)->inside);
}
