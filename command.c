/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoylu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 22:53:07 by esoylu            #+#    #+#             */
/*   Updated: 2022/05/24 23:02:49 by esoylu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*tokenize_command(char *command)
{
	t_command	*cmd;
	char		**tokenized;

	cmd = (t_command *)malloc(sizeof(t_command));
	tokenized = my_split(clear_tabs(command), ' ', cmd);
	cmd = create_elem(tokenized, cmd);
	return (cmd);
}

int	unclosed(char *line)
{
	int	ct1;
	int	ct2;
	int	i;

	ct1 = 0;
	ct2 = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'' && !ct2)
			ct1 = !ct1;
		if (line[i] == '\"' && !ct1)
			ct2 = !ct2;
	}
	return (ct1 || ct2);
}

t_command	*tokenize_input(char *line)
{
	char		**commands;
	t_command	*cmd;
	t_command	*cur;
	int			i;

	i = 0;
	if (unclosed(line))
	{
		printf("error: there is an unclosed quote\n");
		return (0);
	}
	commands = pipe_split(line, '|');
	free(line);
	cmd = tokenize_command(commands[0]);
	cur = cmd;
	free(commands[i]);
	while (commands[++i])
	{
		cur->next = tokenize_command(commands[i]);
		cur->next->prev = cur;
		cur = cur->next;
		free(commands[i]);
	}
	free(commands);
	return (cmd);
}

void	execute_one_cmd_extra(t_command *cmd, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (!pid)
		last_check(cmd, env);
	waitpid(-1, &status, WUNTRACED);
	g_data->last_pid = WEXITSTATUS(status);
}
