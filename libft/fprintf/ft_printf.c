/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 16:47:19 by abarriel          #+#    #+#             */
/*   Updated: 2017/01/10 02:10:46 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_init(t_stock *s)
{
	char		*n_arg;
	t_flag		*f;

	f = set_flags();
	if (!(n_arg = ft_strchr(s->str, '%')))
	{
		free(f);
		return ;
	}
	f->color_nfun = s->color_nfun;
	n_arg++;
	f->b_sta = 0;
	s->tmp = n_arg;
	while ((get_conv(n_arg, f)))
		get_flags(n_arg++, f);
	get_bonus(s, f);
	s->tmp = (n_arg + 1);
	handles_conv(f, s);
	s->f_len += putstr_per(s->tmp);
	s->f_len += f->final_len;
	s->str = s->tmp;
	free(f);
	ft_init(s);
}

int		ft_printf(const char *format, ...)
{
	t_stock	*s;
	size_t	flen;

	s = set_stock(format);
	va_start(s->aps, format);
	color_fun(s);
	flen = putstr_per(s->str);
	ft_init(s);
	flen += s->f_len;
	va_end(s->aps);
	free(s);
	return (flen);
}
