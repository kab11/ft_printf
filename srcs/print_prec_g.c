/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prec_g.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 20:03:22 by mikim             #+#    #+#             */
/*   Updated: 2017/04/26 17:42:48 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	delete_zero(char **tmp)
{
	char	*trail;
	int		i;

	i = ft_strlen(*tmp) - 1;
	while (tmp[0][i] == '0' && i >= 0)
		i--;
	trail = ft_strsub(*tmp, 0, i + 1);
	free(*tmp);
	*tmp = trail;
}

void	ftoa_prec_fg(t_env *e, long double d, int end)
{
	char	*tmp;
	char	*nb;
	long	num;
	int		prec;

	tmp = ft_ltoa((long)d);
	prec = ft_strlen(tmp);
	num = get_prec_num_f(d, end);
	nb = ft_ftoa(num);
	if (end == prec)
		e->out = ft_strdup(tmp);
	else
		e->out = ft_str_prec(nb, prec, prec + end, e->flag.hash);
	if (!e->flag.hash)
		delete_zero(&e->out);
	free(tmp);
	free(nb);
}

void	ftoa_prec_eg(t_env *e, long double d, char type, int prec)
{
	char	*tmp;
	char	*nb;
	char	*expo;
	long	num;

	prec = (prec == 1 ? 0 : prec);
	num = get_prec_num_e(d, prec);
	nb = ft_ftoa(num);
	get_exponent(d, type, &expo);
	tmp = ft_str_prec(nb, 1, prec - 1, e->flag.hash);
	if (!e->flag.hash)
		delete_zero(&tmp);
	e->out = ft_strjoin(tmp, expo);
	free(nb);
	free(tmp);
	free(expo);
}

void	check_form(t_env *e, long double d, char type)
{
	char	*nb;
	int		neg;

	neg = (d < 0 ? -1 : 1);
	d *= neg;
	if ((d + 0.5 > 1000000 || d < 0.0001) && e->flag.prec < 0)
		return (ftoa_prec_eg(e, d * neg, type - 2, 5));
	else if (e->flag.prec < 0)
		return (ftoa_prec_fg(e, d * neg, 6));
	nb = ft_ltoa((long)d);
	if (((int)ft_strlen(nb) > e->flag.prec && e->flag.prec != 0) ||
		(e->flag.prec == 0 && d >= 10))
	{
		free(nb);
		return (ftoa_prec_eg(e, d * neg, type - 2, e->flag.prec));
	}
	free(nb);
	ftoa_prec_fg(e, d * neg, e->flag.prec);
}

void	print_prec_g(t_env *e, long double d, char type)
{
	check_form(e, d, type);
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
