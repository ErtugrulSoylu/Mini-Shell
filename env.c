/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoylu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 22:53:16 by esoylu            #+#    #+#             */
/*   Updated: 2022/05/24 22:53:17 by esoylu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_path(char *name, char **env)
{
	struct dirent	*dir;
	DIR				*d;
	int				i;

	i = -1;
	while (env[++i])
	{
		d = opendir(env[i]);
		while (1)
		{
			dir = readdir(d);
			if (!dir)
				break ;
			if (!ft_strcmp(dir->d_name, name))
			{
				closedir(d);
				return (ft_strjoin(env[i], ft_strjoin("/", dir->d_name)));
			}
		}
		closedir(d);
	}
	free(name);
	return (0);
}

char	*get_path(char *name)
{
	char	*path;
	char	**env;

	if (name[0] == '/')
		return (name);
	path = get_env(ft_strdup("PATH"));
	if (!path)
		return (0);
	path = ft_strchr(path, '=') + 1;
	env = ft_split(path, ':');
	return (search_path(name, env));
}

void	quit(int sig)
{
	(void)sig;
	exit(131);
}

void	ctrlc(int sig)
{
	(void)sig;
	if (!g_data->keep)
		kill_processes();
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	siginit(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrlc);
}
