/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prec_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 18:57:18 by mikim             #+#    #+#             */
/*   Updated: 2017/04/27 21:16:00 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_a_expo(double d, char type, char **expo)
{
	char	*tmp;
	char	pre[3];
	int		i;

	i = 0;
	pre[2] = '\0';
	pre[1] = (d < 0 ? '-' : '+');
	d < 0 ? d *= -1 : 0;
	pre[0] = type + 15;
	while (d >= 2)
	{
		d /= 2;
		i++;
	}
	tmp = ft_itoa(i);
	*expo = ft_strjoin(pre, tmp);
	free(tmp);
}

void	hex_prec(t_env *e, double d, char **frac, char type)
{
	unsigned long	cmp;
	long			num;
	int				len;
	int				cnt;
	int				i;

	len = (e->flag.prec < 0 ? 13 : e->flag.prec);
	*frac = ft_strnew(len);
	cmp = 0x0008000000000000;
	i = -1;
	num = *(long*)&d;
	while (++i < len)
	{
		cnt = 0;
		cnt += (num & cmp) == 0 ? 0 : 8;
		cmp >>= 1;
		cnt += (num & cmp) == 0 ? 0 : 4;
		cmp >>= 1;
		cnt += (num & cmp) == 0 ? 0 : 2;
		cmp >>= 1;
		cnt += (num & cmp) == 0 ? 0 : 1;
		cmp >>= 1;
		frac[0][i] = (cnt < 10 ? cnt + 48 : cnt + type - 25);
	}
}

void	ftoa_prec_a(t_env *e, double d, char type)
{
	char	*x;
	char	*frac;
	char	*expo;
	char	*tmp;

	x = (type == 'a' ? ft_strdup("0x1.") : ft_strdup("0X1."));
	hex_prec(e, d, &frac, type);
	get_a_expo(d, type, &expo);
	tmp = ft_strjoin(x, frac);
	free(x);
	free(frac);
	x = ft_strjoin(tmp, expo);
	free(tmp);
	free(expo);
	e->out = x;
}

void	print_prec_a(t_env *e, double d, char type)
{
	ftoa_prec_a(e, d, type);
	if (e->flag.minus)
	{
		if (d > 0 && (e->flag.plus || e->flag.sp))
			e->ret += (e->flag.plus == 1 ?
			write(e->fd, "+", 1) : write(e->fd, " ", 1));
		e->ret += write(e->fd, e->out, ft_strlen(e->out));
		print_prec_width(e);
	}
	else
	{
		print_prec_width(e);
		if (d > 0 && (e->flag.plus || e->flag.sp))
			e->ret += (e->flag.plus == 1 ?
			write(e->fd, "+", 1) : write(e->fd, " ", 1));
		e->ret += write(e->fd, e->out, ft_strlen(e->out));
	}
	free(e->out);
	e->i++;
}
