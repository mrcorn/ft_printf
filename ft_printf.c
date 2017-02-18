/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 22:27:23 by mchen             #+#    #+#             */
/*   Updated: 2017/02/06 21:02:12 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	ft_vfdprintf(int fd, const char *format, va_list a_list)
{
	t_placehold	*p;
	const char	*e;
	size_t		count;

	count = 0;
	if (format)
	{
		p = malloc(sizeof(*p));
		e = format;
		while (*format)
		{
			if (*format == '%')
			{
				e = format + 1;
				eval_fields(p, &e, a_list);
				count += print_eval(fd, p, a_list, count);
				format = e;
			}
			else
				count += ft_putchar_fd(*(format), fd);
			format += *format ? 1 : 0;
		}
		free(p);
	}
	return (count);
}

int	ft_fdprintf(int fd, const char *format, ...)
{
	va_list a_list;
	size_t	count;

	va_start(a_list, format);
	count = ft_vfdprintf(fd, format, a_list);
	va_end(a_list);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list a_list;
	size_t	count;

	va_start(a_list, format);
	count = ft_vfdprintf(1, format, a_list);
	va_end(a_list);
	return (count);
}
/*
#include <limits.h>
#include <stdio.h>
# include <locale.h>
int main()
{
    //setlocale(LC_CTYPE, "");
	double d = .19487534534367567;
	printf("pp%.15f\n", d);
	ft_printf("ft%.15f\n", d);
	printf("pp%.5f\n", d);
	ft_printf("ft%.5f\n", d);
	printf("pp{%f}\n", 1.42);
	ft_printf("ft{%f}\n", 1.42);
	printf("pp{%.6F}\n", 1.42);
	ft_printf("ft{%.6F}\n", 1.42);
	printf("pp{%.6F}\n", 0.0);
	ft_printf("ft{%.6F}\n", 0.0);
	printf("pp%.15g\n", d);
	ft_printf("ft%.15g\n", d);
	printf("pp%.5g\n", d);
	ft_printf("ft%.5g\n", d);
	printf("pp{%g}\n", 1.42);
	ft_printf("ft{%g}\n", 1.42);
	printf("pp{%.6G}\n", 1.42);
	ft_printf("ft{%.6G}\n", 1.42);
	printf("pp{%.6G}\n", 0.0);
	ft_printf("ft{%.6G}\n", 0.0);
	//printf("%lc:\n", i);
	//printf("pp%.15f\n", 1.0/0);
	return 0;
}
*/