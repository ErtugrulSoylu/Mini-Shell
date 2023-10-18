/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoylu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 22:54:15 by esoylu            #+#    #+#             */
/*   Updated: 2022/05/24 22:54:17 by esoylu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_here_doc_extra(char **file, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		*file = join(*file, ft_strdup(line));
		*file = join(*file, ft_strdup("\n"));
		if (line)
			free(line);
	}
	if (line)
		free(line);
}

void	execute_here_doc(t_command *cmd, char **env, char *delimiter)
{
	char	*file;
	int		fd[2];
	pid_t	pid;

	signal(SIGQUIT, SIG_IGN);
	file = ft_strdup("");
	execute_here_doc_extra(&file, delimiter);
	pipe(fd);
	pid = fork();
	cmd->pid = pid;
	if (!pid)
	{
		signal(SIGQUIT, quit);
		dup2(fd[0], STDIN);
		last_check(cmd, env);
	}
	dup2(fd[1], STDOUT);
	printf("%s", file);
	usleep(100000);
	kill(pid, SIGINT);
	if (file)
		free(file);
	free(delimiter);
	wait(&pid);
}

void	last_check(t_command *cmd, char **env)
{
	char	*check;

	check = cmd->args[0];
	if (!ft_strcmp(check, "echo"))
		builtin_echo(cmd);
	else if (!get_path(cmd->args[0]))
	{
		printf("%s: command not found\n", cmd->args[0]);
		exit(127);
	}
	else
		execve(get_path(cmd->args[0]), cmd->args, env);
	exit(0);
}

void	del_arg(t_command *cmd, int index)
{
	int	i;

	i = 0;
	while (i != index)
		i++;
	free(cmd->args[i]);
	cmd->args[i] = cmd->args[i + 1];
	while (cmd->args[++i])
		cmd->args[i] = cmd->args[i + 1];
}
