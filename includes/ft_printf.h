/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 14:29:51 by mikim             #+#    #+#             */
/*   Updated: 2017/10/14 23:34:55 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <wchar.h>
# include <limits.h>
# include <stdint.h>

# define PF_FLAG " #*+-.s123456789Lhjltz"
# define PF_HEX "boxBOX"
# define PF_UINT "duiDUI"
# define PF_PREC "ageAGE"
# define FT_ISNUM(x) (x >= '0' && x <= '9')

typedef struct	s_pf_tag
{
	int			tag;
	int			pos;
}				t_pf_tag;

typedef struct	s_pf_flag
{
	int			sp;
	int			plus;
	int			neg;
	int			minus;
	int			hash;
	int			zero;
	int			prec;
	int			width;
}				t_pf_flag;

typedef enum	e_pf_mod
{
	pf_nomod = 0,
	pf_h,
	pf_hh,
	pf_l,
	pf_ll,
	pf_j,
	pf_z,
	pf_t,
	pf_L
}				t_pf_mod;

typedef	struct	s_pf_env
{
	va_list		ap[2];
	char		*out;
	t_pf_tag	tag;
	t_pf_flag	flag;
	t_pf_mod	mod;
	int			fd;
	int			i;
	int			ret;
}				t_pf_env;

/*
**				ft_printf
*/

int				ft_printf(const char *restrict fmt, ...);
void			init_env(t_pf_env *e);
void			init_flag(t_pf_flag *flag);
void			print_conversion(const char *restrict fmt, t_pf_env *e);

/*
**				parse_arg
*/

void			get_tag(const char *restrict fmt, t_pf_env *e);
void			get_flag(const char *restrict fmt, t_pf_env *e);
void			get_prec(const char *restrict fmt, t_pf_env *e);
void			get_width(t_pf_env *e);
void			get_mod(const char *restrict fmt, t_pf_env *e);
void			get_spec(const char *restrict fmt, t_pf_env *e);
void			get_spec_more(const char *restrict fmt, t_pf_env *e);

/*
**				init_args
*/

void			init_char_arg(t_pf_env *e, int *tmp);
void			init_str_arg(t_pf_env *e, char **tmp);
void			init_int_arg(t_pf_env *e, long *tmp);
void			init_prec_arg(t_pf_env *e, double *tmp);
void			init_long_double(t_pf_env *e, long double *tmp);
void			init_wchar_arg(t_pf_env *e, wchar_t *tmp);
void			init_wstr_arg(t_pf_env *e, wchar_t **tmp);

/*
**				get_spec
*/

void			spec_fd(t_pf_env *e);
void			spec_int(t_pf_env *e);
void			spec_unsint(t_pf_env *e, char type);
void			spec_char(t_pf_env *e, char type);
void			spec_wchar(t_pf_env *e, char type);
void			spec_precision(t_pf_env *e, char type);
void			spec_base(t_pf_env *e, char type);
void			spec_return(t_pf_env *e);
void			spec_ptraddr(t_pf_env *e, char type);
void			spec_non_printable(t_pf_env *e);
void			spec_percent(t_pf_env *e);

/*
**				print_digit
*/

void			print_digit(t_pf_env *e);
void			print_digit_width(t_pf_env *e);
void			print_digit_sign(t_pf_env *e);
void			check_digit_sign(t_pf_env *e);
void			check_digit_prec(t_pf_env *e);

/*
**				print_base
*/

void			print_base(t_pf_env *e, char type, long val);
void			print_base_width(t_pf_env *e, char type);
void			print_base_pre(t_pf_env *e, char type, long val);
void			check_base_prec(t_pf_env *e, char type);

/*
**				print_char
*/

void			print_char(t_pf_env *e, char c);
void			print_null_char(t_pf_env *e);
void			print_char_width(t_pf_env *e);
void			print_str(t_pf_env *e);
void			print_null_str(t_pf_env *e);
void			print_str_width(t_pf_env *e);

/*
**				print_wchar
*/

void			print_wchar(t_pf_env *e, wchar_t wc);
void			print_wchar_minus(t_pf_env *e, wchar_t wc);
void			print_wstr(t_pf_env *e, wchar_t *wc);
void			print_wstr_minus(t_pf_env *e, wchar_t *wc, int len);
int				get_wstr_len(wchar_t *wc);
void			put_wstr(t_pf_env *e, wchar_t c);
void			put_wstr_c(t_pf_env *e, char c);

/*
** 				print_prec_tools
*/

void			nan_inf(t_pf_env *e, char type, double var);
void			nan_inf_long(t_pf_env *e, char type, long double var);
void			print_prec_width(t_pf_env *e);
char			*ft_ftoa(long double d);
char			*ft_str_prec(char *s1, int dot, int end, int hash);

/*
** 				print_prec_a
*/

void			print_prec_a(t_pf_env *e, double d, char type);
void			print_prec_a_else(t_pf_env *e, double d, char type);
void			ftoa_prec_a(t_pf_env *e, double d, char type);
void			hex_prec(t_pf_env *e, double d, char **frac, char type);
void			get_a_expo(double d, char type, char **expo);

/*
** 				print_prec_e
*/

void			print_prec_e(t_pf_env *e, long double d, char type);
void			ftoa_prec_e(t_pf_env *e, long double d, char type);
long			get_prec_num_e(long double d, int prec);
void			get_exponent(long double d, char type, char **expo);

/*
**				print_prec_f
*/

void			print_prec_f(t_pf_env *e, long double d);
void			ftoa_prec_f(t_pf_env *e, long double d);
long			get_prec_num_f(long double d, int prec);

/*
** 				print_prec_g
*/

void			print_prec_g(t_pf_env *e, long double d, char type);
void			check_form(t_pf_env *e, long double d, char type);
void			ftoa_prec_eg(t_pf_env *e, long double d, char type, int prec);
void			ftoa_prec_fg(t_pf_env *e, long double d, int end);
void			delete_zero(char *tmp);

/*
**				print_ptraddr
*/

void			print_ptraddr(t_pf_env *e, char type);
void			print_ptraddr_width(t_pf_env *e);
void			ptraddr_prec(t_pf_env *e);

/*
**				print_invalid
*/

void			print_invalid_spec(t_pf_env *e, char c);
void			print_invalid_width(t_pf_env *e);

/*
**				print_non_printable
*/

void			print_non_printable(t_pf_env *e);
void			print_zero_to_ten(t_pf_env *e, char c);
void			print_ten_to_twenty(t_pf_env *e, char c);
void			print_twenty_to_thirty(t_pf_env *e, char c);

/*
**				print_dice
*/

void			print_dice(t_pf_env *e);

/*
**				settings
*/

void			check_settings(const char *restrict fmt, t_pf_env *e);
void			set_colo(const char *restrict fmt, t_pf_env *e);
void			set_light_colo(const char *restrict fmt, t_pf_env *e);
void			set_bg_colo(const char *restrict fmt, t_pf_env *e);
void			set_options(const char *restrict fmt, t_pf_env *e);

/*
**				libft
*/

void			ft_bzero(void *s, size_t n);
void			ft_strlower(char *s);
char			*ft_strchr(const char *s, int c);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strdup(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnew(size_t size);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
int				ft_atoi(const char *str);
char			*ft_itoa(int n);
char			*ft_ltoa(long n);
char			*ft_ltoa_base(long n, int base);
char			*ft_uitoa(unsigned int n);
char			*ft_ultoa(unsigned long n);
char			*ft_uitoa_base(unsigned int n, int base);
char			*ft_ultoa_base(unsigned long n, int base);

/*
**				SETTINGS	EFFECT		COLORS
**				{OFF}		OFF SETTING	BLK		BLACK
**				{SET:BO}	BOLD		RED		RED
**				{SET:FT}	FAINT		GRN		GREEN
**				{SET:IT}	ITALIC		YEL		YELLOW
**				{SET:UL}	UNDERLINE	BLU		BLUE
**				{SET:RE}	REVERSE		MGT		MAGENTA
**				{SET:CC}	CONCEAL		CYN		CYAN
**				{SET:RV}	REVEAL		WHT		WHITE
**				{BGC:***}	BACKGROUND
**				{LT:***]	LIGHT COLO
*/

#endif
