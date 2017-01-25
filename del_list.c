/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 21:52:56 by abarriel          #+#    #+#             */
/*   Updated: 2017/01/21 22:46:13 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	lstdelone(t_info **alst)
{
	if (alst)
	{
		free((*alst)->name);
		free(*alst);
		*alst = NULL;
	}
}

void	lstdel(t_info **alst)
{
	t_info *new;

	if (alst)
	{
		while (*alst)
		{
			new = (*alst)->next;
			lstdelone(alst);
			(*alst) = new;
		}
		(*alst) = NULL;
	}
}

void	lstdelone_d(t_info **alst)
{
	t_info *new;

	if (alst)
	{
		while ((*alst)->inside)
		{
			new = (*alst)->inside->next;
			if ((*alst)->inside)
			{
				free((*alst)->inside->name);
				free((*alst)->inside);
				(*alst)->inside = NULL;
			}
			((*alst)->inside) = new;
		}
		free((*alst)->name);
		free(*alst);
		*alst = NULL;
	}
}

void	lstdel_d(t_info **alst)
{
	t_info *new;

	if (alst)
	{
		while (*alst)
		{
			new = (*alst)->next;
			lstdelone_d(alst);
			(*alst) = new;
		}
		(*alst) = NULL;
	}
}
