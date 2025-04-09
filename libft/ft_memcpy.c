/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:38:41 by badam             #+#    #+#             */
/*   Updated: 2021/12/01 23:07:55 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dstcpy;
	unsigned char	*srccpy;

	if (!dst && !src && n)
		return (NULL);
	dstcpy = (unsigned char *)dst;
	srccpy = (unsigned char *)src;
	while (n--)
		*(dstcpy++) = *(srccpy++);
	return (dst);
}
