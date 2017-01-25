/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_long_format_.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 20:49:06 by abarriel          #+#    #+#             */
/*   Updated: 2017/01/23 20:49:16 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	get_nine(struct stat sb)
{
	char	nine;

	if (sb.st_mode & S_IXUSR)
		nine = 'x';
	else
		nine = '-';
	if (sb.st_mode & S_ISUID)
	{
		if (sb.st_mode & 0100)
			nine = 's';
		else
			nine = 'S';
	}
	return (nine);
}

char	get_five(struct stat sb)
{
	char	five;

	if (sb.st_mode & S_IXGRP)
		five = 'x';
	else
		five = '-';
	if (sb.st_mode & S_ISGID)
	{
		if (sb.st_mode & 0010)
			five = 's';
		else
			five = 'S';
	}
	return (five);
}

char	get_eight(struct stat sb)
{
	char	eight;

	if (sb.st_mode & S_IXOTH)
		eight = 'x';
	else
		eight = '-';
	if (sb.st_mode & S_ISVTX)
	{
		if (sb.st_mode & 0100)
			eight = 't';
		else
			eight = 'T';
	}
	return (eight);
}
