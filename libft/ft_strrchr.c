/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:43:03 by badam             #+#    #+#             */
/*   Updated: 2021/12/01 23:16:42 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*strcpy;

	strcpy = (unsigned char *)s;
	while (*strcpy)
		strcpy++;
	while (*strcpy != (unsigned char)c && strcpy != (unsigned char *)s)
		strcpy--;
	if ((unsigned char)c == *strcpy)
		return ((char *)strcpy);
	else
		return (NULL);
}
