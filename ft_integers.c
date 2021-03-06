/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_integers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 22:26:36 by mchen             #+#    #+#             */
/*   Updated: 2017/02/21 19:46:24 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

char				*ft_uitoa_base(uintmax_t value, unsigned short base,
						unsigned short uppercase, int digits)
{
	char	*ret;
	char	*dig;
	int		i;

	dig = "0123456789abcdef0123456789ABCDEF";
	dig += 16 * uppercase;
	if ((ret = malloc(sizeof(*ret) * (MAX(ft_uintmax_len(value, base), digits)
		+ 1))))
	{
		i = 0;
		while (value != 0 || (i == 0 && digits != 0) || i < digits)
		{
			ret[i++] = dig[value % base];
			value /= base;
		}
		ret[i] = 0;
		ft_strrev(ret);
	}
	return (ret);
}

static intmax_t		cast_signed_size_t(intmax_t num)
{
	if (sizeof(size_t) == sizeof(short))
		return ((short)num);
	else if (sizeof(size_t) == sizeof(int))
		return ((int)num);
	else if (sizeof(size_t) == sizeof(long))
		return ((long long)num);
	else if (sizeof(size_t) == sizeof(long long))
		return ((long long)num);
	else
		return (num);
}

static intmax_t		cast_intmax(intmax_t num, t_placehold *p)
{
	if (p->length != NULL)
	{
		if (!ft_strcmp(p->length, "hh"))
			return ((char)num);
		else if (!ft_strcmp(p->length, "h"))
			return ((short)num);
		else if (!ft_strcmp(p->length, "l"))
			return ((long)num);
		else if (!ft_strcmp(p->length, "ll"))
			return ((long long)num);
		else if (!ft_strcmp(p->length, "j"))
			return (num);
		else if (!ft_strcmp(p->length, "z"))
			return (cast_signed_size_t(num));
	}
	return ((int)num);
}

static uintmax_t	cast_uintmax(uintmax_t num, t_placehold *p)
{
	if (p->length != NULL)
	{
		if (!ft_strcmp(p->length, "hh"))
			return ((unsigned char)num);
		else if (!ft_strcmp(p->length, "h"))
			return ((unsigned short)num);
		else if (!ft_strcmp(p->length, "l"))
			return ((unsigned long)num);
		else if (!ft_strcmp(p->length, "ll"))
			return ((unsigned long long)num);
		else if (!ft_strcmp(p->length, "j"))
			return (num);
		else if (!ft_strcmp(p->length, "z"))
			return ((size_t)num);
	}
	else if (p->type == 'p')
		return (num);
	return ((unsigned int)num);
}

/*
** Handles %dDioOuUxXbp. Casts it appropriately, stores its sign in p,
** then returns the unsigned number as string.
*/

char				*ft_printf_itoa_base(t_placehold *p, va_list a_list)
{
	intmax_t	sint;
	uintmax_t	uint;

	if (p->signed_num == 1)
	{
		sint = cast_intmax(va_arg(a_list, intmax_t), p);
		if (sint < 0)
		{
			p->sign = '-';
			uint = -sint;
		}
		else
			uint = sint;
	}
	else
		uint = cast_uintmax(va_arg(a_list, uintmax_t), p);
	if ((uint == 0 && (!ft_strchr("poO", p->type) || (p->hash &&
		ft_strchr("oO", p->type) && p->prec))) || (p->hash &&
		ft_strchr("oO", p->type) && p->prec > 0))
		p->hash = NULL;
	else if (uint > 0)
		p->prec = MAX(ft_uintmax_len(uint, p->base), p->prec);
	return (ft_uitoa_base(uint, p->base, p->uppercase, p->prec));
}
