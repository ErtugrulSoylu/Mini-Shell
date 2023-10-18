/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoylu <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 21:11:02 by esoylu            #+#    #+#             */
/*   Updated: 2022/01/10 12:54:21 by esoylu           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncpy(char const *src, unsigned int n)
{
	char			*dest;
	unsigned int	i;

	if (n == 0)
		return (0);
	dest = (char *)malloc((n + 1) * sizeof(char));
	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	all_len(char const *str, char c)
{
	int	i;
	int	count;

	if (c == '\0')
	{
		if (ft_strlen(str) == 0)
			return (1);
		else
			return (2);
	}
	count = 0;
	while (*str == c)
		str++;
	while (*str)
	{
		i = 0;
		while (str[i] && str[i] != c)
			i++;
		count++;
		while (str[i] && str[i] == c)
			i++;
		str = &str[i];
	}
	return (count + 1);
}

char	**ft_split(char const *str, char c)
{
	char	**ret;
	int		ret_index;
	int		i;

	if (!str)
		return (0);
	ret = (char **)malloc(all_len(str, c) * sizeof(char *));
	if (ret == 0)
		return (0);
	ret_index = 0;
	while (*str && *str == c)
		str++;
	while (*str)
	{
		i = 0;
		while (str[i] && str[i] != c)
			i++;
		ret[ret_index++] = ft_strncpy(str, i);
		while (str[i] && str[i] == c)
			i++;
		str = &str[i];
	}
	ret[ret_index] = 0;
	return (ret);
}
