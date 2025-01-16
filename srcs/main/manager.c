/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:06:51 by arafa             #+#    #+#             */
/*   Updated: 2024/06/13 10:35:31 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_fd(t_data *data, char *input_str);

int		analyse_input(char *input);

void	re_initialize(t_data *data, char *input_str)
{
	int	x;

	x = 0;
	if (input_str)
		free(input_str);
	data->cmd.pipes = -1;
	dup2(data->_stdin, STDIN_FILENO);
	dup2(data->_stdout, STDOUT_FILENO);
	while (x < 1000)
	{
		data->fd[x][0] = 0;
		data->fd[x][1] = 0;
		x++;
	}
	data->index = 0;
	data->index_trigger = 0;
	g_res_stdinfileno = 0;
}

void	new_cwd(t_data *data)
{
	if (data->mini.cwd != NULL)
		free(data->mini.cwd);
	data->mini.cwd = malloc(sizeof (char) * 1024);
	getcwd(data->mini.cwd, 1024);
}

void	loop2(t_data *data, char *input_str, int *original_stdin)
{
	if (g_res_stdinfileno == 1)
		dup2(*original_stdin, STDIN_FILENO);
	else if (!input_str)
	{
		free(input_str);
		rl_clear_history();
		printf("^D\n");
		exit_manager(data, input_str);
	}
}

char	*set_deco(t_data *data)
{
	char	*temp;
	char	*deco;
	char	*user;

	temp = NULL;
	deco = NULL;
	if (!(data->mini.logname))
		user = "Unknown";
	else
		user = data->mini.logname;
	deco = ft_strjoin("\001\033[38;5;197m\002 ", user);
	temp = ft_strjoin(deco, "\001\033[38;5;33m\002 ");
	free(deco);
	deco = ft_strjoin(temp, data->mini.cwd);
	free(temp);
	temp = ft_strjoin(deco, "\001\033[0m\033[38;5;197m\002 : \001\033[0m\002");
	free(deco);
	return (temp);
}

void	loop(t_data *data, int *original_stdin)
{
	static char	*input_str;

	while (1)
	{
		*original_stdin = dup(STDIN_FILENO);
		data->deco = set_deco(data);
		input_str = readline(data->deco);
		free(data->deco);
		loop2(data, input_str, original_stdin);
		if (!just_space(input_str, 0))
			change_input_str(&data->mini, &input_str);
		if (input_str && !just_space(input_str, 0)
			&& !analyse_input(input_str))
		{
			init_cmd(&data->cmd, input_str);
			set_fd(data, data->cmd.input_str);
			new_cwd(data);
			pipex(data);
			new_cwd(data);
			free_cmd(&data->cmd);
		}
		g_res_stdinfileno = 0;
		close(*original_stdin);
		re_initialize(data, input_str);
	}
}
