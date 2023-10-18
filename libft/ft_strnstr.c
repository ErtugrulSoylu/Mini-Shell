/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoylu <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 03:03:19 by esoylu            #+#    #+#             */
/*   Updated: 2022/01/10 06:32:41 by esoylu           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t maxlen)
{
	size_t	len;

	len = ft_strlen(needle);
	if (len == 0)
		return ((char *)haystack);
	while (*haystack)
	{
		if (len > maxlen)
			break ;
		if (ft_strncmp(haystack, needle, len) == 0)
			return ((char *)haystack);
		haystack++;
		maxlen--;
	}
	return (0);
}
