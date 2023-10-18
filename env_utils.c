/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagirdem <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:34:36 by cagirdem          #+#    #+#             */
/*   Updated: 2022/04/26 00:07:38 by cagirdem         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(char **env)
{
	int	i;
	int	env_length;

	g_data->infd = dup(STDIN);
	g_data->outfd = dup(STDOUT);
	g_data->keep = 1;
	i = -1;
	while (env[++i] != NULL)
		;
	env_length = i;
	g_data->env_p = (char **)malloc(sizeof(char *) * 40);
	i = -1;
	while (++i < env_length)
		g_data->env_p[i] = ft_strdup(env[i]);
	siginit();
	g_data->keep = 1;
}

char	*get_env(char *env_key)
{
	int	i;

	if (ft_strcmp(env_key, "?") == 0)
	{
		free(env_key);
		return (join(ft_strdup("?="), ft_itoa(g_data->last_pid)));
	}
	i = -1;
	while (g_data->env_p[++i])
	{
		if (!ft_strncmp(g_data->env_p[i], env_key, ft_strlen(env_key)))
		{
			free(env_key);
			return (g_data->env_p[i]);
		}
	}
	free(env_key);
	return (0);
}

int	set_env(char *env_key, char *env_value)
{
	int	i;

	i = -1;
	if (!env_value || !env_value[0])
		env_value = "";
	while (g_data->env_p[++i])
	{
		if (!ft_strncmp(g_data->env_p[i], env_key, ft_strlen(env_key)))
		{
			env_key = join(env_key, ft_strdup("="));
			env_key = join(env_key, ft_strdup(env_value));
			free(g_data->env_p[i]);
			g_data->env_p[i] = ft_strdup(env_key);
			free(env_key);
			return (0);
		}
	}
	env_key = join(env_key, ft_strdup("="));
	env_key = join(env_key, ft_strdup(env_value));
	free(g_data->env_p[i]);
	g_data->env_p[i] = ft_strdup(env_key);
	free(env_key);
	return (0);
}

int	unset_env(char *tmp)
{
	int		i;
	char	*env_key;

	if (ft_strchr(tmp, '='))
	{	
		printf("invalid parameter name\n");
		return (1);
	}
	env_key = ft_strjoin(tmp, "=");
	i = -1;
	while (g_data->env_p[++i])
	{
		if (!ft_strncmp(g_data->env_p[i], env_key, ft_strlen(env_key)))
		{
			free(g_data->env_p[i]);
			g_data->env_p[i] = g_data->env_p[i + 1];
			while (g_data->env_p[++i])
				g_data->env_p[i] = g_data->env_p[i + 1];
		}
	}
	free(env_key);
	return (0);
}

void	kill_processes(void)
{
	while (g_data->cmd)
	{
		kill(SIGINT, g_data->cmd->pid);
		g_data->cmd = g_data->cmd->next;
	}
}
