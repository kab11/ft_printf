/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prec_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 18:57:18 by mikim             #+#    #+#             */
/*   Updated: 2017/04/28 01:06:34 by mikim            ###   ########.fr       */
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
	d < 0 ? d *= -1 : 0;
	pre[1] = (d > 0 ? '+' : '-');
	pre[0] = type + 15;
	while (d >= 2 || d < 1)
	{
		if (d < 1)
			d *= 2;
		else
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
		frac[0][i] = (cnt < 10 ? cnt + 48 : cnt + type - 10);
	}
}

void	delete_a_zero(char *frac)
{
	int		i;

	i = ft_strlen(frac);
	while (--i >= 0 && frac[i] == '0')
		frac[i] = '\0';
}

void	ftoa_prec_a(t_env *e, double d, char type)
{
	char	*frac;
	char	*ep;
	char	*tmp;

	hex_prec(e, d, &frac, type);
	delete_a_zero(frac);
	get_a_expo(d, type, &ep);
	if (frac[0] == '\0')
		e->out = (type == 'a' ? ft_strjoin("0x1", ep) : ft_strjoin("0X1", ep));
	else
	{
		tmp = (type == 'a' ?
		ft_strjoin("0x1.", frac) : ft_strjoin("0X1.", frac));
		e->out = ft_strjoin(tmp, ep);
		free(tmp);
	}
	free(frac);
	free(ep);
	if (d < 0)
	{
		tmp = ft_strjoin("-", e->out);
		free(e->out);
		e->out = tmp;
	}
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
