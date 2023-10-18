/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoylu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 22:53:57 by esoylu            #+#    #+#             */
/*   Updated: 2022/05/24 22:53:58 by esoylu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	switchfds(int fd[4])
{
	close(fd[0]);
	close(fd[1]);
	fd[0] = fd[2];
	fd[1] = fd[3];
}

void	closefds(int fd[4])
{
	close(fd[1]);
	close(fd[3]);
	usleep(10000);
	close(fd[0]);
	close(fd[2]);
}

pid_t	execute_pipe_process(t_command *cmd, char **env, int fd[4])
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		signal(SIGQUIT, quit);
		if (cmd->prev)
			dup2(fd[0], STDIN);
		if (cmd->next)
			dup2(fd[3], STDOUT);
		closefds(fd);
		execute_one_cmd(cmd, env);
	}
	return (pid);
}

void	execute_pipe(t_command *cmd, char **env, int fd[4])
{
	cmd->pid = execute_pipe_process(cmd, env, fd);
	switchfds(fd);
	pipe(fd + 2);
	if (cmd->next)
		execute_pipe(cmd->next, env, fd);
	closefds(fd);
	wait (&cmd->pid);
}

void	execute_command(t_command *cmd, char **env)
{
	int	fd[4];
	int	status;
	int	ret_val;

	if (!cmd || !cmd->args[0])
		return ;
	if (!cmd->next)
		return (execute_one_cmd(cmd, env));
	pipe(fd);
	pipe(fd + 2);
	execute_pipe(cmd, env, fd);
	ret_val = waitpid(-1, &status, WUNTRACED);
	g_data->last_pid = WEXITSTATUS(status);
	closefds(fd);
}
