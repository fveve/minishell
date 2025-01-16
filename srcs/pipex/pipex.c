/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:39:15 by arafa             #+#    #+#             */
/*   Updated: 2024/06/14 16:23:18 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_data *data, char *cmd, int trigger);

void	pipex2(t_data *data)
{
	int	x;

	x = 0;
	data->index_trigger = data->index - 1;
	data->index = 0;
	signal(SIGINT, SIG_IGN);
	while (data->cmd.pipes > 0)
	{
		exec_child(data, x);
		x++;
		data->index++;
		data->cmd.pipes--;
	}
	if (data->fd[data->index][1] >= 0)
		dup2(data->fd[data->index][1], STDOUT_FILENO);
	while (data->cmd.cmds[x])
	{
		exec_cmd(data, data->cmd.cmds[x], 0);
		x++;
	}
}

void	pipex(t_data *data)
{
	int	x;

	x = 0;
	pipex2(data);
	dup2(data->_stdin, 0);
	while (data->index >= 0)
	{
		close(data->fd[x][0]);
		close(data->fd[x][1]);
		close(0);
		waitpid(-1, &g_sig_error_code, 0);
		x++;
		data->index--;
	}
	if (WIFEXITED(g_sig_error_code))
		g_sig_error_code = WEXITSTATUS(g_sig_error_code);
	signal(SIGINT, handle_signal);
}
