/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 22:26:48 by mchen             #+#    #+#             */
/*   Updated: 2017/02/03 22:32:54 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void			set_hash(t_placehold *p, const char *e)
{
	if (p->hash || ft_strchr("paA", *e))
	{
		if (ft_strchr("oO", *e))
			p->hash = "0";
		else if (ft_strchr("pxa", *e))
			p->hash = "0x";
		else if (ft_strchr("XA", *e))
			p->hash = "0X";
		else if (*e == 'b')
			p->hash = "0b";
		else
		{
			p->hash = NULL;
			return ;
		}
		p->sign = 0;
	}
}

static void		init_placehold(t_placehold *p)
{
	p->leftalign = 0;
	p->sign = 0;
	p->padding = ' ';
	p->hash = NULL;
	p->width = 0;
	p->prec = -1;
	p->length = NULL;
	p->type = 0;
	p->base = 10;
	p->signed_num = 0;
	p->uppercase = 0;
	p->sigfig = -1;
	p->exp_base = 10;
	p->exp_char = 0;
	p->exp_len = 2;
}

void			eval_fields(t_placehold *p, const char **e, va_list a_list)
{
	init_placehold(p);
	set_flag_field(p, e);
	set_width_field(p, e, a_list);
	set_precision_field(p, e, a_list);
	set_length_field(p, e);
	set_type_field(p, *e);
}

static size_t	ft_puteval(int fd, t_placehold *p, char *str, size_t slen)
{
	size_t	count;

	count = 0;
	if (p->padding == '0')
	{
		count += (p->sign ? ft_putchar_fd(p->sign, fd) : 0);
		count += ft_putstr_fd(p->hash, fd);
	}
	if (!p->leftalign)
		count += ft_putnchar_fd(fd, p->padding, p->width - slen);
	if (p->padding == ' ')
	{
		count += (p->sign ? ft_putchar_fd(p->sign, fd) : 0);
		count += ft_putstr_fd(p->hash, fd);
	}
	count += ft_putnstr_fd(fd, str, ft_strlen(str));
	count += (p->type && (ft_strchr("cC", p->type) && ft_strlen(str) == 0) ?
		ft_putchar_fd(*str, fd) : 0);
	if (p->leftalign)
		count += ft_putnchar_fd(fd, p->padding, p->width - slen);
	if (p->length)
		free(p->length);
	return (count);
}

size_t			print_eval(int fd, t_placehold *p, va_list a_list, size_t cnt)
{
	char	*str;
	size_t	slen;
	size_t	count;

	str = NULL;
	if (p->type && ft_strchr("dDioOuUxXbp", p->type))
		str = ft_printf_itoa_base(p, a_list);
	else if (p->type && ft_strchr("fFeEgGaA", p->type))
		str = ft_printf_ftoa(p, a_list);
	else if (p->type && ft_strchr("cC", p->type))
		str = ft_printf_ctos(p, a_list);
	else if (p->type && ft_strchr("sS", p->type))
		str = ft_printf_str(p, p->prec, a_list);
	else if (p->type && p->type == 'n')
		*va_arg(a_list, int*) = cnt;
	else if ((str = ft_memalloc(sizeof(*str) * 2)))
		*str = p->type;
	if (p->type == 'n')
		return (0);
	slen = (ft_strchr("cC", p->type) && ft_strlen(str) == 0 ? 1 :
		ft_strlen(str)) + ft_strlen(p->hash) + (p->sign != 0 ? 1 : 0);
	count = ft_puteval(fd, p, str, slen);
	if (str)
		free(str);
	return (count);
}
