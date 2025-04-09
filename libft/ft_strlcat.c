/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:16:46 by badam             #+#    #+#             */
/*   Updated: 2021/12/01 23:02:43 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*dstcpy;
	char	*srccpy;
	size_t	dstlen;
	size_t	srclen;
	size_t	dstsizecpy;

	dstcpy = (char *)dst;
	srccpy = (char *)src;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	dstsizecpy = dstsize - dstlen;
	if (dstsize && dstsizecpy <= dstsize && dstsizecpy)
	{
		dstcpy = dstcpy + dstlen;
		while (*srccpy && dstsizecpy && --dstsizecpy)
			*(dstcpy++) = *(srccpy++);
		*dstcpy = '\0';
	}
	if (dstsize < dstlen)
		return (dstsize + srclen);
	else
		return (dstlen + srclen);
}
