/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagirdem <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 15:03:58 by cagirdem          #+#    #+#             */
/*   Updated: 2022/05/28 05:28:56 by cagirdem         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(int indicator)
{
	int	i;

	i = -1;
	while (g_data->env_p[++i])
	{
		if (indicator)
			printf("declare -x ");
		printf("%s\n", g_data->env_p[i]);
	}
}

void	builtin_pwd(t_command *cmd)
{
	int	i;

	i = -1;
	while (cmd->args[++i])
		;
	printf("%s\n", ft_strchr(get_env(ft_strdup("PWD=")), '=') + 1);
}

int	builtin_cd(t_command *cmd)
{
	char	cwd[4097];

	if (cmd->args[1] && chdir(cmd->args[1]) != 0)
	{
		printf("cd: no such file or directory: %s\n", cmd->args[1]);
		return (-1);
	}
	set_env(ft_strdup("OLDPWD"), ft_strchr(get_env(ft_strdup("PWD")), '=') + 1);
	getcwd(cwd, 4096);
	set_env(ft_strdup("PWD"), cwd);
	return (0);
}

void	builtin_unset(t_command *cmd)
{
	int	i;

	i = -1;
	while (cmd->argv[++i])
	{
		if (!ft_strncmp(cmd->argv[i], "=", 1))
		{
			printf("%s not found\n", cmd->argv[i]);
			return ;
		}
	}	
	while (i > 1)
	{
		g_data->last_pid = unset_env(cmd->argv[i - 1]);
		i--;
	}
}
