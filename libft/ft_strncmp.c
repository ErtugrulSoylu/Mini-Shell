/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoylu <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:32:34 by esoylu            #+#    #+#             */
/*   Updated: 2022/01/10 01:02:46 by esoylu           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *p1, const char *p2, size_t count)
{
	register const char	*s1;
	register const char	*s2;
	unsigned int		n;

	n = (unsigned int)count;
	s1 = p1;
	s2 = p2;
	if (n == 0)
		return (0);
	while (n-- != 0)
	{
		if (*s1 != *s2++)
			return ((unsigned char)*s1 - (unsigned char)*--s2);
		if (*s1++ == 0)
			break ;
	}
	return (0);
}
