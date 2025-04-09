/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 19:40:35 by badam             #+#    #+#             */
/*   Updated: 2021/12/01 22:59:06 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*init_array(size_t strlen)
{
	char	*str;

	str = malloc(sizeof(char) * strlen);
	if (!str)
		return (NULL);
	str[strlen] = '\0';
	str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	int		positive;
	long	posinb;
	int		posinbcpy;
	size_t	strlen;
	char	*str;

	positive = (n >= 0);
	strlen = 2 + !positive;
	posinb = (long)n * positive + -1 * !positive * (long)n;
	posinbcpy = posinb;
	while (posinbcpy / 10)
	{
		posinbcpy /= 10;
		strlen++;
	}
	str = init_array(--strlen);
	if (!str)
		return (NULL);
	while (strlen - !positive > 0)
	{
		str[--strlen] = '0' + (posinb % 10);
		posinb /= 10;
	}
	return (str);
}
