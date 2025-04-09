/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:16:44 by badam             #+#    #+#             */
/*   Updated: 2021/12/01 23:41:38 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*hscpy;
	char	*hscpycpy;
	char	*ndcpy;

	hscpy = (char *)haystack;
	if (!*needle)
		return (hscpy);
	while (*hscpy)
	{
		ndcpy = (char *)needle;
		hscpycpy = hscpy;
		while (*(hscpycpy++) == *(ndcpy++)
			&& len >= ((size_t)(hscpy - (char *)haystack
				+ ndcpy - (char*)needle)))
		{
			if (!*ndcpy)
				return (hscpy);
		}
		hscpy++;
	}
	return (NULL);
}
