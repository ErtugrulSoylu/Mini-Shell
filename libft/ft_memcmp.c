/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoylu <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 21:07:57 by esoylu            #+#    #+#             */
/*   Updated: 2022/01/10 00:28:28 by esoylu           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	register const unsigned char	*p1;
	register const unsigned char	*p2;

	p1 = s1;
	p2 = s2;
	while (n-- > 0)
	{
		if (*p1++ != *p2++)
			return (*--p1 - *--p2);
	}
	return (0);
}
