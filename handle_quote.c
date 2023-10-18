/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoylu <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 21:11:02 by esoylu            #+#    #+#             */
/*   Updated: 2022/05/24 23:04:33 by esoylu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char const *src, unsigned int n)
{
	char			*dest;
	unsigned int	i;

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
	int		ret_index;
	int		i;

	ret_index = 0;
	while (*str && *str == c)
		str++;
	while (*str)
	{
		i = 0;
		while (str[i] && str[i] != c && str[i] != '\'' && str[i] != '\"')
			i++;
		ret_index++;
		i++;
		if (str[i - 1] == '\'')
			while (str[i] && str[i] != '\'')
				i++;
		if (str[i - 1] == '\"')
			while (str[i] && str[i] != '\"')
				i++;
		while (str[i] && str[i] == c)
			i++;
		str = &str[i];
	}
	return (ret_index + 1);
}

char	*get_between(char const *str, int *k)
{
	char	*ret;
	int		i;
	char	*tmp;

	i = *k;
	if (str[i] == '\'' && ft_strchr(str + 1, '\''))
	{
		tmp = ft_strchr(str + i + 1, '\'');
		ret = ft_strncpy(str + i + 1, tmp - str - i - 1);
		*k = ft_strchr(str + i + 1, '\'') - str + 1;
	}
	else if (str[i] == '\"' && ft_strchr(str + i + 1, '\"'))
	{
		tmp = ft_strchr(str + i + 1, '\"');
		ret = ft_strncpy(str + i + 1, tmp - str - i - 1);
		ret = handle_env_vars(ret);
		*k = ft_strchr(str + i + 1, '\"') - str + 1;
	}
	else
		ret = (char *)str;
	return (ret);
}

void	extra(char *str, int *i, char **ret, char **argv)
{
	if (str[*i] == '\'' || str[*i] == '\"')
	{
		*ret = get_between(str, i);
		*argv = ft_strdup(*ret);
	}
	else
	{
		*ret = ft_strncpy(str, *i);
		*argv = ft_strdup(*ret);
		*ret = handle_env_vars(*ret);
	}
}

char	**my_split(char *str, char c, t_command *cmd)
{
	char	**ret;
	int		ret_index;
	int		i;

	ret = (char **)malloc(all_len(str, c) * sizeof(char *));
	cmd->argv = (char **)malloc(all_len(str, c) * sizeof(char *));
	ret_index = 0;
	while (*str && *str == c)
		str++;
	while (*str)
	{
		i = 0;
		while (str[i] && str[i] != c && str[i] != '\'' && str[i] != '\"')
			i++;
		extra(str, &i, &ret[ret_index], &cmd->argv[ret_index]);
		ret_index++;
		while (str[i] && str[i] == c)
			i++;
		str = &str[i];
	}
	ret[ret_index] = 0;
	cmd->argv[ret_index] = 0;
	return (ret);
}
