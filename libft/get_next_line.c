/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 22:07:24 by abarriel          #+#    #+#             */
/*   Updated: 2016/12/11 21:11:19 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				read_line(t_stocks *stock)
{
	char		buff[BUFF_SIZE + 1];
	int			ret;
	char		*tmp;

	while ((ret = read(stock->fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = stock->data;
		stock->data = ft_strjoin(tmp, buff);
		ft_strdel(&tmp);
	}
	if (ret == -2)
		return (ret);
	return (1);
}

int				get_line(char **line, t_stocks *stock)
{
	*line = ft_strchr(stock->data, '\n');
	if (*line == NULL)
	{
		*line = ft_strchr(stock->data, '\0');
		if (ft_strlen(stock->data) == 0)
			return (0);
	}
	return (1);
}

t_stocks		*create_stock(int fd)
{
	t_stocks *newstock;

	newstock = (t_stocks*)malloc(sizeof(t_stocks));
	if (!newstock)
		return (NULL);
	newstock->fd = fd;
	newstock->data = ft_strnew(0);
	newstock->next = NULL;
	return (newstock);
}

t_stocks		*get_stock(int fd)
{
	static t_stocks		*stock = NULL;
	t_stocks			*tmp;

	tmp = stock;
	while (tmp)
	{
		if (fd == tmp->fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (stock)
	{
		tmp = create_stock(fd);
		tmp->next = stock;
		stock = tmp;
	}
	return (stock = create_stock(fd));
}

int				get_next_line(int fd, char **line)
{
	int				i;
	char			*tmp;
	t_stocks		*stock;

	if (fd < 0 || line == NULL || BUFF_SIZE < 1)
		return (-1);
	*line = NULL;
	stock = get_stock(fd);
	if (read_line(stock) == -1)
		return (-1);
	i = get_line(line, stock);
	if (i == 0)
	{
		stock->fd = 0;
		return (0);
	}
	tmp = stock->data;
	*line = ft_strsub(tmp, 0, *line - tmp);
	stock->data = ft_strsub(tmp + 1, ft_strlen(*line), ft_strlen(tmp + 1));
	ft_strdel(&tmp);
	return (1);
}
