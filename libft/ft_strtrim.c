/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoylu <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 02:15:12 by esoylu            #+#    #+#             */
/*   Updated: 2022/01/10 12:53:52 by esoylu           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strhas(char const c, char const *set)
{
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		res_index;
	char	*res;

	if (!s1)
		return (0);
	i = 0;
	res_index = 0;
	j = ft_strlen(s1) - 1;
	while (strhas(s1[i], set) && i <= j)
		i++;
	while (strhas(s1[j], set) && i <= j)
		j--;
	if (j - i + 2 == 1)
		return (ft_strdup(""));
	res = (char *)malloc((j - i + 2) * sizeof(char));
	if (res == 0)
		return (0);
	while (i <= j)
		res[res_index++] = s1[i++];
	res[res_index] = '\0';
	return (res);
}
