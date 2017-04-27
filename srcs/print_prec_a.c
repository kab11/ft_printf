/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prec_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 18:57:18 by mikim             #+#    #+#             */
/*   Updated: 2017/04/26 17:41:14 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_a_expo(double d, char type, char **expo)
{
	char	*tmp;
	long	num;
	long	cmp;
	int		cnt;
	int		i;

	cmp = 0x0800000000000000;
	i = -1;
	num = (long)d;
	cnt = 0;
	while (i < 11)
	{
		cnt *= 2;
		cnt += (num & cmp) == 0 ? 1 : 0;
		cmp >>= 1;
	}
	cnt -= 1023;
	tmp = ft_itoa(cnt);
	*expo = ft_strjoin(&type, tmp);
	free(tmp);
}

char	*hex_prec(t_env *e, double d, char type)
{
	char	*frac;
	long	num;
	long	cmp;
	int		cnt;
	int		i;

	frac = ft_strnew(e->flag.prec >= 0 ? 13 : e->flag.prec);
	cmp = 0x0008000000000000;
	i = -1;
	num = (long)d;
	while (frac[++i] != '\0')
	{
		cnt = 0;
		cnt += (num & cmp) == 0 ? 8 : 1;
		cmp >>= 1;
		cnt += (num & cmp) == 0 ? 4 : 1;
		cmp >>= 1;
		cnt += (num & cmp) == 0 ? 2 : 1;
		cmp >>= 1;
		cnt += (num & cmp) == 0 ? 1 : 1;
		cmp >>= 1;
		frac[i] = (cnt < 10 ? cnt + 48 : cnt + type - 25);
	}
	return (frac);
}

void	ftoa_prec_a(t_env *e, double d, char type)
{
	char	*x;
	char	*frac;
	char	*expo;
	char	*tmp;

	x = (type == 'p' ? ft_strdup("0x1.") : ft_strdup("0X1."));
	frac = hex_prec(e, d, type);
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
}
