/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 16:47:27 by mikim             #+#    #+#             */
/*   Updated: 2017/04/27 18:57:40 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_wchar(t_env *e, int c)
{
	write(e->fd, &c, 1);
}

void	print_wchar_minus(t_env *e, wchar_t wc)
{
	put_wchar(e, (int)wc);
	while (e->flag.width-- > 1)
		e->ret += write(e->fd, " ", 1);
}

void	print_wchar(t_env *e, wchar_t wc)
{
	if (e->flag.minus)
		print_wchar_minus(e, wc);
	else
	{
		while (e->flag.width-- > 1)
			e->ret += (e->flag.zero ?
			write(e->fd, "0", 1) : write(e->fd, " ", 1));
		put_wchar(e, (int)wc);
	}
	e->i++;
}
