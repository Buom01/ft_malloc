/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 20:22:07 by badam             #+#    #+#             */
/*   Updated: 2020/04/09 03:22:07 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	strlen;
	char	*fstr;
	char	*fstrcpy;

	if (!s || !f)
		return (NULL);
	strlen = ft_strlen(s);
	fstr = ft_substr(s, 0, strlen + 1);
	if (!fstr)
		return (NULL);
	fstrcpy = fstr;
	while (*fstrcpy)
	{
		*fstrcpy = f((unsigned int)(fstrcpy - fstr), (char)(*fstrcpy));
		fstrcpy++;
	}
	return (fstr);
}
