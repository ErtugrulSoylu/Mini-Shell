/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoylu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 22:54:48 by esoylu            #+#    #+#             */
/*   Updated: 2022/05/24 22:54:53 by esoylu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_quit(int sig)
{
	(void)sig;
	if (g_data->flag)
		printf("Quit\n");
	g_data->flag = 0;
}

int	line_check(char *line)
{
	if (!line)
		exit(0);
	if (!line[0])
	{
		free(line);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_command	*command;

	(void)argc;
	(void)argv;
	g_data = (t_data *)malloc(sizeof(t_data));
	init(env);
	while (1)
	{
		line = readline("\033[1;32m$ \033[0m");
		if (!line_check(line))
			continue ;
		add_history(line);
		command = tokenize_input(line);
		g_data->flag = 1;
		signal(SIGQUIT, main_quit);
		g_data->keep = 0;
		execute_command(command, g_data->env_p);
		g_data->keep = 1;
		signal(SIGQUIT, SIG_IGN);
		del_elem(command);
	}
	return (0);
}
