/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:29:15 by badam             #+#    #+#             */
/*   Updated: 2021/12/01 23:29:35 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*strcpy;
	unsigned char	charcpy;

	strcpy = (unsigned char *)s;
	charcpy = (unsigned char)c;
	if (n)
	{
		while (n && --n && charcpy != *strcpy)
			strcpy++;
		if (charcpy == *strcpy)
			return ((void *)strcpy);
		else
			return (NULL);
	}
	else
		return (NULL);
}
