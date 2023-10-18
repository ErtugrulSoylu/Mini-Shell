/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_funcs_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagirdem <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 21:19:00 by cagirdem          #+#    #+#             */
/*   Updated: 2022/04/26 00:21:51 by cagirdem         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_export(t_command *cmd)
{
	int		args_count;
	char	**inline_args;

	args_count = 1;
	while (cmd->args[args_count] != 0)
		args_count++;
	if (args_count == 1)
		builtin_env(1);
	else
	{
		while (args_count-- > 1)
		{
			if (!ft_strchr(cmd->args[args_count], '='))
				continue ;
			inline_args = ft_split(cmd->args[args_count], '=');
			if (!inline_args[0] && !inline_args[1])
				return (free2d(inline_args, 1));
			else if (cmd->args[args_count][0] == '=')
				return (free2d(inline_args, 2));
			set_env(ft_strdup(inline_args[0]), inline_args[1]);
			free2d(inline_args, 0);
		}
	}
}

void	builtin_echo(t_command *cmd)
{
	int	i;
	int	check;

	check = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (!ft_strcmp(cmd->args[i], "-n"))
		{
			check = 1;
			del_arg(cmd, i--);
		}
		i++;
	}
	i = 1;
	while (cmd->args[i] != NULL)
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (!check)
		printf("\n");
}

void	handle_env_vars_extra(char *line, int *i, int *j)
{
	*i += *j + 1;
	*j = *i - 1;
	while (line[*i] && line[*i] != '$' && line[*i] != ' ')
		*i = *i + 1;
}

char	*handle_env_vars(char *line)
{
	char	*ret;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	ret = ft_strdup("");
	while (1)
	{
		if (!ft_strchr(&line[i], '$'))
		{
			ret = join(ret, ft_strdup(&line[i]));
			break ;
		}
		j = ft_strchr(&line[i], '$') - &line[i];
		ret = join(ret, ft_substr(line, i, j));
		handle_env_vars_extra(line, &i, &j);
		tmp = get_env(ft_substr(line, j + 1, i - j - 1));
		if (tmp && ft_strchr(tmp, '='))
			ret = join(ret, ft_strdup(ft_strchr(tmp, '=') + 1));
		if (tmp && tmp[0] == '?' && tmp[1] == '=')
			free(tmp);
	}
	free(line);
	return (ret);
}

void	builtin_exit(t_command *cmd)
{
	int	i;

	i = -1;
	while (cmd->argv[++i])
		;
	if (i > 2)
	{
		printf("exit: too many arguments\n");
		g_data->last_pid = 1;
	}
	else if (cmd->argv[1])
	{
		exit(ft_atoi(cmd->argv[1]));
	}
	else
	{
		exit(0);
	}
}
