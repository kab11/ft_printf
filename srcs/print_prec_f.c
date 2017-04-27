/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prec_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 20:03:22 by mikim             #+#    #+#             */
/*   Updated: 2017/04/26 17:41:21 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long	get_prec_num_f(long double d, int prec)
{
	int		neg;
	int		i;

	i = -1;
	neg = (d < 0 ? -1 : 1);
	d *= neg;
	while (++i < prec)
		d *= 10;
	d += 0.5;
	d *= neg;
	return ((long)d);
}

void	ftoa_prec_f(t_env *e, long double d)
{
	char	*tmp;
	char	*nb;
	long	num;
	int		prec;

	tmp = ft_ltoa((long)d);
	prec = ft_strlen(tmp);
	num = get_prec_num_f(d, (e->flag.prec >= 0 ? e->flag.prec : 6));
	nb = ft_ftoa(num);
	if (e->flag.prec == 0)
		e->out = ft_strdup(tmp);
	else
		e->out = ft_str_prec(nb, prec, e->flag.prec != -1 ?
		prec + e->flag.prec : prec + 6, e->flag.hash);
	free(nb);
	free(tmp);
}

void	print_prec_f(t_env *e, long double d)
{
	ftoa_prec_f(e, d);
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
	e->i++;
	free(e->out);
}
