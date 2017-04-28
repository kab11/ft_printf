/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 16:47:27 by mikim             #+#    #+#             */
/*   Updated: 2017/04/27 17:41:56 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_wchar(t_env *e, char c)
{
	write(e->fd, &c, 1);
}

void	put_wc(t_env *e, wchar_t c)
{
	if (c <= 0x7F)
		put_wchar(e, c);
	else if (c <= 0x7FF)
	{
		put_wchar(e, (c >> 6) + 0xC0);
		put_wchar(e, (c & 0x3F) + 0x80);
	}
	else if (c <= 0xFFFF)
	{
		put_wchar(e, ((c >> 12) + 0xE0));
		put_wchar(e, ((c >> 6) & 0x3F) + 0x80);
		put_wchar(e, (c & 0x3F) + 0x80);
	}
	else if (c <= 0x10FFFF)
	{
		put_wchar(e, (c >> 18) + 0xF0);
		put_wchar(e, ((c >> 12) & 0x3F) + 0x80);
		put_wchar(e, ((c >> 6) & 0x3F) + 0x80);
		put_wchar(e, (c & 0x3F) + 0x80);
	}
	e->ret++;
}

int		get_wchar_len(wchar_t *wc)
{
	int i;
	int len;

	i = -1;
	len = 0;
	while (wc[++i] != 0)
	{
		if (wc[i] <= 0x7F)
			len++;
		else if (wc[i] <= 0x7FF)
			len ++;
		else if (wc[i] <= 0xFFFF)
			len ++;
		else if (wc[i] <= 0x10FFFF)
			len ++;
	}
	return (len);
}

void	print_wchar_minus(t_env *e, wchar_t *wc, int len)
{
	int i;

	i = -1;
	if (e->flag.prec >= 0)
	{
		while (wc[++i] != 0 && i < e->flag.prec)
			put_wc(e, wc[i]);
	}
	else
	{
		while (wc[++i] != 0)
			put_wc(e, wc[i]);
	}
	while (e->flag.width-- > len)
		e->ret += (e->flag.zero == 1 ?
		write(e->fd, "0", 1) : write(e->fd, " ", 1));
}

void	print_wchar(t_env *e, wchar_t *wc)
{
	int i;
	int len;

	i = -1;
	len = (e->flag.prec < 0 ? get_wchar_len(wc) : e->flag.prec);
	if (e->flag.minus)
		print_wchar_minus(e, wc, len);
	else
	{
		while (e->flag.width-- > len)
			e->ret += (e->flag.zero == 1 ?
			write(e->fd, "0", 1) : write(e->fd, " ", 1));
		if (e->flag.prec >= 0)
			while (wc[++i] != 0 && i < e->flag.prec)
				put_wc(e, wc[i]);
		else
			while (wc[++i] != 0)
				put_wc(e, wc[i]);
	}
	e->i++;
}
