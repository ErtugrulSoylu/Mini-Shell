/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoylu <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 21:01:19 by esoylu            #+#    #+#             */
/*   Updated: 2022/01/10 06:33:38 by esoylu           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if ((char *)dst == 0 && (char *)src == 0)
		return (dst);
	if (dst > src)
	{
		while (len-- > 0)
			((char *)dst)[len] = ((char *)src)[len];
	}
	else
	{
		i = -1;
		while (++i < len)
			((char *)dst)[i] = ((char *)src)[i];
	}
	return (dst);
}
