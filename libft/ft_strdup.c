/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 17:17:02 by badam             #+#    #+#             */
/*   Updated: 2021/12/01 23:17:30 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	strlen;
	char	*strdup;
	size_t	strdupcur;

	strlen = ft_strlen(s1) + 1;
	strdup = malloc(strlen * sizeof(char));
	if (!strdup)
		return (NULL);
	strdupcur = 0;
	while (strdupcur < strlen)
	{
		strdup[strdupcur] = s1[strdupcur];
		strdupcur++;
	}
	return (strdup);
}
