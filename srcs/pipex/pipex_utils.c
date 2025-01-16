/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:21:22 by arafa             #+#    #+#             */
/*   Updated: 2024/06/14 16:21:14 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_parent(t_data *data, int pid, int pipe_fd[2])
{
	if (pid)
	{

		if (data->fd[data->index][0])
			dup2(data->fd[data->index][0], 0);
		else if (pipe_fd[0])
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0], 0);
		}
		if (data->fd[data->index][1])
			dup2(data->fd[data->index][1], 1);
		else
			dup2(data->_stdout, 1);
	}
}

char	*set_path(t_data *data, char *tab)
{
	char	*path;

	path = NULL;
	if (is_slash(tab))
		path = ft_strdup(tab);
	else
		path = find_path(tab, data->mini.env);
	return (path);
}

char	**set_tab(char *cmd)
{
	char	**tab;

	tab = NULL;
	tab = ft_split(cmd, " ", 0);
	tab = remove_space(tab);
	return (tab);
}

char	**find_path2(char **env)
{
	char	**env2;
	int		x;

	x = 0;
	env2 = NULL;
	while (env[x] != NULL)
	{
		if (is_path(env[x]))
		{
			env2 = ft_split(env[x], ":", 1);
			return (env2);
		}
		x++;
	}
	printf("No path defined\n");
	exit(0);
	return (env2);
}

void	exec_cmd3(t_data *data)
{
	if (!data->cmd.is_pipe)
	{
		close(data->fd[data->index][0]);
		close(data->fd[data->index][1]);
		close(0);
		dup2(data->_stdin, 0);
		waitpid(-1, &g_sig_error_code, 0);
	}
}
