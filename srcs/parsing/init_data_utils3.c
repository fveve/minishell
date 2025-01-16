/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:10:47 by arafa             #+#    #+#             */
/*   Updated: 2024/06/14 14:47:06 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_redirection(char *input_str, char *new_str, char *old_str);

int		is_comma(char *input);

char	*init_cmd2(t_cmd *cmd, char *input_str, char *old_str)
{
	char	*new_str;

	new_str = NULL;
	if (is_redirection(input_str))
	{
		cmd->trigger = 1;
		new_str = remove_redirection(input_str, new_str, old_str);
	}
	else
		new_str = ft_strdup(input_str);
	return (new_str);
}

void	init_cmd(t_cmd *cmd, char *input_str)
{
	char	*old_str;
	char	*new_str;

	new_str = NULL;
	old_str = NULL;
	cmd->is_pipe = 0;
	cmd->trigger = 0;
	new_str = init_cmd2(cmd, input_str, old_str);
	cmd->pipes = -1;
	if (is_pipes(cmd, new_str))
		cmd->cmds = ft_split(new_str, "|;", 1);
	else if (is_comma(new_str))
		cmd->cmds = ft_split(new_str, ";", 1);
	else
	{
		cmd->cmds = malloc(sizeof(char *) * 2);
		cmd->cmds[0] = ft_strdup(new_str);
		cmd->cmds[1] = NULL;
	}
	cmd->cmds = remove_space(cmd->cmds);
	cmd->input_str = ft_strdup(input_str);
	free(new_str);
}

char	*set_input(char *input_str, int *x)
{
	while (input_str[*x] && input_str[*x] != ' ' && input_str[*x] != '|')
	{
		input_str[*x] = ' ';
		(*x)++;
	}
	return (input_str);
}

char	*remove_redirection3(char **temp, char *old_str, char *new_str)
{
	int	x;

	x = 2;
	old_str = ft_strjoin(temp[0], temp[1]);
	while (temp[x])
	{
		if (new_str)
			free(new_str);
		new_str = ft_strjoin(old_str, temp[x]);
		free(old_str);
		old_str = ft_strdup(new_str);
		x++;
	}
	if (ft_strlen2(temp) == 2)
	{
		if (new_str)
			free(new_str);
		new_str = ft_strdup(old_str);
	}
	free(old_str);
	return (new_str);
}

void	init_data2(t_data *data)
{
	int	x;

	x = 0;
	while (x < 1000)
	{
		data->fd[x][0] = 0;
		data->fd[x][1] = 0;
		x++;
	}
}
