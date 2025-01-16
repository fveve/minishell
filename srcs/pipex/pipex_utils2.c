/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:26:27 by arafa             #+#    #+#             */
/*   Updated: 2024/06/14 12:46:00 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_data *data, char *cmd, int trigger);

void	exec_child2(t_data *data, pid_t pid, int x, int pipe_fd[2])
{
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		close(pipe_fd[0]);
		if (data->fd[data->index][1])
		{
			dup2(data->fd[data->index][1], 1);
			close(data->fd[data->index][1]);
		}
		else
			dup2(pipe_fd[1], 1);
		exec_cmd(data, data->cmd.cmds[x], 1);
		exit_manager(data, "");
	}
}

void	skip_comma(char *input, int *x)
{
	if (input[*x] == '\'')
	{
		(*x)++;
		while (input[*x] && input[*x] != '\'')
			(*x)++;
	}
	if (input[*x] == '\"')
	{
		(*x)++;
		while (input[*x] && input[*x] != '\"')
			(*x)++;
	}
}
