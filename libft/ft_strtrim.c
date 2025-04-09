/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 13:17:15 by badam             #+#    #+#             */
/*   Updated: 2021/12/01 23:08:59 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*scpy;
	size_t	trimdlen;
	size_t	trimbgn;

	if (!s1 || !set)
		return (NULL);
	scpy = (char *)s1;
	trimdlen = 0;
	while (*scpy && ft_strchr(set, (int)(*scpy)))
		scpy++;
	trimbgn = scpy - (char *)s1;
	while (*(scpy + 1))
		scpy++;
	while (ft_strrchr(set, (int)(*scpy)))
		scpy--;
	trimdlen = scpy - (char *)s1 - trimbgn + 1;
	return (ft_substr(s1, trimbgn, trimdlen));
}
