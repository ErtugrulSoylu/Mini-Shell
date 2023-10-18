/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoylu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 22:55:08 by esoylu            #+#    #+#             */
/*   Updated: 2022/05/24 22:55:09 by esoylu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clear_tabs(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\t')
			str[i] = ' ';
	return (str);
}

t_command	*create_elem(char **argv, t_command *new_elem)
{
	new_elem->next = 0;
	new_elem->prev = 0;
	new_elem->args = argv;
	return (new_elem);
}

void	del_elem(t_command *cmd)
{
	if (!cmd)
		return ;
	free2d(cmd->args, 0);
	free2d(cmd->argv, 0);
	del_elem(cmd->next);
	free(cmd);
}

void	free2d(char **arr, int error_no)
{
	int	i;

	if (error_no == 1)
		printf("bad assignment\n");
	if (error_no == 2)
	{
		g_data->last_pid = 1;
		printf("%s not found\n", arr[0]);
	}
	if (!arr)
		return ;
	i = -1;
	while (arr[++i] != 0)
		free(arr[i]);
	free(arr);
}

char	*join(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	res = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	i = 0;
	j = 0;
	while (s1 && s1[j])
		res[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (res);
}
