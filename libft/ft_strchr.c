/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:23:08 by badam             #+#    #+#             */
/*   Updated: 2021/12/01 23:33:25 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*strcpy;

	strcpy = (unsigned char *)s;
	while (*strcpy != (unsigned char)c && *strcpy)
		strcpy++;
	if ((unsigned char)c == *strcpy)
		return ((char *)strcpy);
	else
		return (NULL);
}
