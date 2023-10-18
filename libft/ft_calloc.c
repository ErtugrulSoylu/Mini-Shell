/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoylu <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 20:26:12 by esoylu            #+#    #+#             */
/*   Updated: 2022/01/10 06:25:41 by esoylu           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;

	if (count * size == 0)
	{
		size = 1;
		count = 1;
	}
	res = (void *)malloc(size * count);
	if (res)
		ft_bzero(res, count * size);
	return (res);
}
