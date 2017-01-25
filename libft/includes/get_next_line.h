/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 00:43:54 by abarriel          #+#    #+#             */
/*   Updated: 2016/12/11 17:05:47 by mheutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1024
# include "libft.h"
# include <fcntl.h>

typedef struct		s_stocks
{
	int				fd;
	int				read;
	char			*data;
	struct s_stocks	*next;
}					t_stocks;

int					get_next_line(int fd, char **line);

#endif
