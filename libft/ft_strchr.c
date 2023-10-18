/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoylu <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 19:55:35 by esoylu            #+#    #+#             */
/*   Updated: 2022/01/10 11:00:43 by arelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	loc;

	loc = 0;
	while (s[loc] && s[loc] != (unsigned char)c)
		loc++;
	if (s[loc] == (unsigned char)c)
		return (&((char *)s)[loc]);
	return (0);
}
