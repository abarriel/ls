/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:38:48 by abarriel          #+#    #+#             */
/*   Updated: 2017/01/23 15:28:19 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_list_reverse(t_info **begin_list)
{
	t_info	*list;
	t_info	*last;
	t_info	*tmp;

	list = *begin_list;
	last = NULL;
	while (list)
	{
		tmp = list->next;
		list->next = last;
		last = list;
		list = tmp;
	}
	*begin_list = last;
}

void	sort_time_r(t_info **begin_list)
{
	ft_list_reverse(begin_list);
}

void	sort_ascii_r(t_info **begin_list)
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

int		cmp_time(t_info *l1, t_info *l2)
{
	if (l1->mtime.tv_sec < l2->mtime.tv_sec)
		return (l1->mtime.tv_sec < l2->mtime.tv_sec);
	else if (l1->mtime.tv_sec == l2->mtime.tv_sec)
	{
		if (l1->mtime.tv_nsec < l2->mtime.tv_nsec)
			return (l1->mtime.tv_nsec < l2->mtime.tv_nsec);
		else if (l1->mtime.tv_nsec == l2->mtime.tv_nsec)
			return (ft_strcmp(l1->name, l2->name));
	}
	return (0);
}

void	sort_time(t_info **begin_list)
{
	t_info	*current;
	t_info	*last;

	current = *begin_list;
	if (!*begin_list)
		return ;
	while (current->next)
	{
		if (cmp_time(current, current->next) > 0)
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
