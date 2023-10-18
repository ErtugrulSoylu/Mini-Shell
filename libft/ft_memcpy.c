/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoylu <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 19:47:36 by esoylu            #+#    #+#             */
/*   Updated: 2022/01/11 17:45:10 by esoylu           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	if ((char *)dst == 0 && (char *)src == 0)
		return (dst);
	while (n-- > 0)
		((char *)dst)[n] = ((char *)src)[n];
	return (dst);
}
