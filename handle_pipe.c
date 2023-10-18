/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoylu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 22:54:26 by esoylu            #+#    #+#             */
/*   Updated: 2022/05/24 22:54:28 by esoylu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_quote(char const *str, int i)
{
	int	j;
	int	q1;
	int	q2;

	j = -1;
	q1 = 0;
	q2 = 0;
	while (str[++j])
	{
		if (str[j] == '\'' && !q2)
			q1 = !q1;
		if (str[j] == '\"' && !q1)
			q2 = !q2;
		if (j == i)
			return (q1 || q2);
	}
	return (0);
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
		while (str[i] && (str[i] != c || in_quote(str, i)))
			i++;
		count++;
		while (str[i] && str[i] == c)
			i++;
		str = &str[i];
	}
	return (count + 1);
}

char	**pipe_split(char const *str, char c)
{
	char	**ret;
	int		ret_index;
	int		i;

	ret = (char **)malloc(all_len(str, c) * sizeof(char *));
	ret_index = 0;
	while (*str && *str == c)
		str++;
	while (*str)
	{
		i = 0;
		while (str[i] && (str[i] != c || in_quote(str, i)))
			i++;
		ret[ret_index++] = ft_strncpy(str, i);
		while (str[i] && str[i] == c)
			i++;
		str = &str[i];
	}
	ret[ret_index] = 0;
	return (ret);
}
