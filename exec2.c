/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoylu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 22:52:57 by esoylu            #+#    #+#             */
/*   Updated: 2022/05/24 23:03:38 by esoylu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_backredirection2(t_command *cmd)
{
	char	*delimiter;
	int		i;

	i = -1;
	delimiter = 0;
	while (cmd->args[++i])
	{
		if (!ft_strcmp(cmd->args[i], "<<"))
		{
			if (!cmd->args[i + 1])
			{
				printf("bash: syntax error near unexpected token `newline'\n");
				exit(2);
			}
			delimiter = ft_strdup(cmd->args[i + 1]);
			del_arg(cmd, i);
			del_arg(cmd, i--);
		}
	}
	return (delimiter);
}

int	check_backredirection(t_command *cmd)
{
	int	i;
	int	fd;

	i = -1;
	fd = 0;
	while (cmd->args[++i])
	{
		if (!ft_strcmp(cmd->args[i], "<"))
		{
			if (!cmd->args[i + 1])
			{
				printf("bash: syntax error near unexpected token `newline'\n");
				exit(2);
			}
			fd = open(cmd->args[i + 1], O_RDONLY, 0777);
			del_arg(cmd, i);
			del_arg(cmd, i--);
		}	
	}
	return (fd);
}

int	check_redirection(t_command *cmd)
{
	int	i;
	int	fd;

	i = -1;
	fd = 1;
	while (cmd->args[++i])
	{
		if (!ft_strcmp(cmd->args[i], ">") || !ft_strcmp(cmd->args[i], ">>"))
		{
			if (!cmd->args[i + 1])
			{
				printf("bash: syntax error near unexpected token `newline'\n");
				exit(2);
			}
			if (cmd->args[i][1] == '>')
				fd = open(cmd->args[i + 1], \
						O_CREAT | O_APPEND | O_WRONLY, 0777);
			else
				fd = open(cmd->args[i + 1], O_TRUNC | O_CREAT | O_WRONLY, 0777);
			del_arg(cmd, i);
			del_arg(cmd, i--);
		}
	}
	return (fd);
}

int	built_in(t_command *cmd)
{
	char	*check;	

	check = cmd->args[0];
	if (!ft_strcmp(check, "cd"))
		builtin_cd(cmd);
	else if (!ft_strcmp(check, "export"))
		builtin_export(cmd);
	else if (!ft_strcmp(check, "unset"))
		builtin_unset(cmd);
	else if (!ft_strcmp(check, "pwd"))
		builtin_pwd(cmd);
	else if (!ft_strcmp(check, "env"))
		builtin_env(0);
	else if (!ft_strcmp(check, "exit"))
		builtin_exit(cmd);
	else
		return (0);
	return (1);
}

void	execute_one_cmd(t_command *cmd, char **env)
{
	char	*delimiter;
	int		infd;
	int		outfd;

	outfd = check_redirection(cmd);
	if (outfd != 1)
		dup2(outfd, STDOUT);
	infd = check_backredirection(cmd);
	delimiter = check_backredirection2(cmd);
	if (infd != 0)
		dup2(infd, STDIN);
	if (delimiter)
		execute_here_doc(cmd, env, delimiter);
	else if (built_in(cmd))
		;
	else
		execute_one_cmd_extra(cmd, env);
	dup2(g_data->infd, STDIN);
	dup2(g_data->outfd, STDOUT);
	if (cmd->next || cmd->prev)
		exit(0);
}
