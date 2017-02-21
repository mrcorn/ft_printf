/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strucase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 19:30:53 by mchen             #+#    #+#             */
/*   Updated: 2016/12/01 20:37:56 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strucase(char *s)
{
	char *str;

	str = s;
	if (s)
	{
		while (*s)
		{
			if (*s >= 'a' && *s <= 'z')
				*s -= 32;
			s++;
		}
	}
	return (str);
}
