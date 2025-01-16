/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:31:14 by marvin            #+#    #+#             */
/*   Updated: 2024/06/14 16:22:09 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd3(t_data *data);

void	exec_child2(t_data *data, pid_t pid, int x, int pipe_fd[2]);

int	is_slash(char	*str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (str[x] == '/')
			return (1);
		x++;
	}
	return (0);
}

int	is_tiret(char *s)
{
	int	x;

	x = 0;
	while (s[x])
	{
		if (s[x] == '-')
			return (1);
		x++;
	}
	return (0);
}

void	exec_cmd2(t_data *data, char *cmd, int trigger, char **temp)
{
	char	*path;
	char	**tab;
	pid_t	pid;

	path = NULL;
	tab = NULL;
	pid = 1 ;
	if (!trigger)
		pid = fork();
	if (!pid || trigger == 1)
	{
		if (data->fd[data->index] >= 0)
			dup2(data->fd[data->index][0], 0);
		signal(SIGINT, SIG_DFL);
		tab = set_tab(cmd);
		path = set_path(data, tab[0]);
		if (execve(path, tab, data->mini.env) < 0)
			perror("Error");
		free_tab(tab);
		free_tab(temp);
		exit_manager(data, path);
	}
	exec_cmd3(data);
}

void	exec_cmd(t_data *data, char *cmd, int trigger)
{
	char	**temp;

	temp = ft_split(cmd, " ", 1);
	if (ft_strncmp(temp[0], "pwd", 10000) == 0)
		pwd_cmd();
	else if (ft_strncmp(temp[0], "cd", 10000) == 0)
		cd_cmd(&data->mini, cmd);
	else if (ft_strncmp(temp[0], "env", 10000) == 0)
		env_cmd(&(data->mini));
	else if (ft_strncmp(temp[0], "export", 10000) == 0)
		export_cmd(&(data->mini), cmd);
	else if (ft_strncmp(temp[0], "unset", 10000) == 0)
		unset_cmd(&data->mini, cmd);
	else if (ft_strncmp(temp[0], "exit", 10000) == 0)
		exit_manager(data, data->cmd.input_str);
	else if (ft_strncmp(temp[0], "echo", 10000) == 0)
		echo_cmd(cmd);
	else if (ft_strncmp(temp[0], "$", 10000) == 0)
		dollar_cmd(data);
	else if (data->cmd.input_str[0])
		exec_cmd2(data, cmd, trigger, temp);
	free_tab(temp);
}

void	exec_child(t_data *data, int x)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe ");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork ");
		return ;
	}
	exec_child2(data, pid, x, pipe_fd);
	set_parent(data, pid, pipe_fd);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
}
