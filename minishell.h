/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoylu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 22:55:01 by esoylu            #+#    #+#             */
/*   Updated: 2022/05/24 23:03:58 by esoylu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

# include <stdio.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include <term.h>
# include <curses.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>

# define BUFFER_SIZE 50
# define STDIN 0
# define STDOUT 1
# define MAX_PIPE 1000

typedef struct s_command
{
	pid_t				pid;
	char				**args;
	char				**argv;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_data
{
	char		**env_p;
	int			pid_list[MAX_PIPE];
	int			flag;
	int			keep;
	int			next;
	int			last_pid;
	int			infd;
	int			outfd;
	t_command	*cmd;
}	t_data;

t_data		*g_data;

char		**my_split(char *str, char c, t_command *cmd);
t_command	*tokenize_input(char *line);
t_command	*create_elem(char **argv, t_command *cmd);
char		*get_path(char *name);
void		execute_command(t_command *cmd, char **env);
void		del_elem(t_command *cmd);
char		*clear_tabs(char *str);
void		execute_pipe(t_command *cmd, char **env, int fd[4]);
void		execute_one_cmd(t_command *cmd, char **env);
void		del_arg(t_command *cmd, int index);
void		last_check(t_command *cmd, char **env);
void		execute_here_doc(t_command *cmd, char **env, char *delimiter);
void		siginit(void);
void		quit(int sig);
void		ctrlc(int sig);
void		kill_processes(void);
char		**pipe_split(char const *str, char c);
char		*ft_strncpy(char const *src, unsigned int n);

void		init(char **env);
char		*get_env(char *env_key);
int			set_env(char *env_key, char *env_value);
int			unset_env(char *env_key);
char		*handle_env_vars(char *line);

void		builtin_env(int indicator);
void		builtin_pwd(t_command *cmd);
int			builtin_cd(t_command *data);
void		builtin_unset(t_command *data);
void		builtin_export(t_command *data);
void		builtin_echo(t_command *data);
void		builtin_exit(t_command *cmd);
void		free2d(char **arr, int error_no);
char		*join(char *s1, char *s2);
void		execute_one_cmd_extra(t_command *cmd, char **env);
void		main_quit(int sig);

#endif
