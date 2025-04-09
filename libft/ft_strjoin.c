/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 18:05:48 by badam             #+#    #+#             */
/*   Updated: 2021/12/01 23:09:59 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strsrccpy;
	size_t	len;
	char	*strdst;
	char	*strdstcpy;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	strdst = malloc((len + 1) * sizeof(char));
	if (!strdst)
		return (NULL);
	strdstcpy = (char *)strdst;
	strsrccpy = (char *)s1;
	while (*strsrccpy)
		*(strdstcpy++) = *(strsrccpy++);
	strsrccpy = (char *)s2;
	while (*strsrccpy)
		*(strdstcpy++) = *(strsrccpy++);
	*strdstcpy = '\0';
	return (strdst);
}
