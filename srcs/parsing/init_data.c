/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:07:07 by marvin            #+#    #+#             */
/*   Updated: 2024/06/13 15:24:34 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd(t_cmd *cmd, char *input_str);

char	*remove_redirection3(char **temp, char *old_str, char *new_str);

void	init_data2(t_data *data);

void	init_mini2(t_mini *mini, char **new_env)
{
	int		i;
	int		j;
	char	**env;

	env = alpha_reorder(new_env);
	i = 0;
	j = 0;
	mini->export_env = malloc(sizeof(char *) * (ft_strlen2(env) + 1));
	while (env[j] != NULL)
	{
		mini->export_env[j] = malloc (sizeof(char) * (ft_strlen(env[j]) + 1));
		while (env[j][i] != '\0')
		{
			mini->export_env[j][i] = env[j][i];
			i++;
		}
		mini->export_env[j][i] = '\0';
		i = 0;
		j++;
	}
	mini->export_env[j] = NULL;
	if (env)
		free_tab(env);
}

void	init_mini(t_mini *mini, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	mini->env = (char **)malloc(sizeof(char *) * (ft_strlen2(env) + 1));
	if (!(mini->env))
	{
		printf("this environment is empty\n");
		exit(0);
	}
	while (env[j] != NULL)
	{
		mini->env[j] = (char *)malloc(sizeof(char) * (ft_strlen(env[j]) + 1));
		while (env[j][i] != '\0')
		{
			mini->env[j][i] = env[j][i];
			i++;
		}
		mini->env[j][i] = '\0';
		i = 0;
		j++;
	}
	mini->env[j] = NULL;
}

char	*remove_redirection2(char *input_str, int trigger)
{
	int	x;
	int	i;

	x = 0;
	i = set_i(input_str, trigger);
	if (i)
	{
		while (i--)
		{
			if (!trigger)
				while (input_str[x] && input_str[x] != '<')
					x++;
			else if (trigger)
				while (input_str[x] && input_str[x] != '>')
					x++;
			if (input_str[x] == '>' || input_str[x] == '<')
				x++;
			if (input_str[x] == '>' || input_str[x] == '<')
				x++;
			while (input_str[x] && input_str[x] == ' ')
				x++;
			input_str = set_input(input_str, &x);
		}
	}
	return (input_str);
}

char	*remove_redirection(char *input_str, char *new_str, char *old_str)
{
	char	**temp;

	old_str = NULL;
	new_str = set_new_str(input_str);
	temp = ft_split(new_str, "<>", 1);
	if (ft_strlen2(temp) > 1 && !just_space(temp[1], 0))
		new_str = remove_redirection3(temp, old_str, new_str);
	else
	{
		free(new_str);
		new_str = ft_strdup(temp[0]);
	}
	free_tab(temp);
	return (new_str);
}

void	init_data(t_data *data, char **env)
{
	data->index = 0;
	init_mini(&data->mini, env);
	init_mini2(&data->mini, env);
	data->mini.cwd = NULL;
	data->mini.logname = NULL;
	new_cwd(data);
	data->cmd.pipes = -1;
	init_logname(&data->mini);
	data->cmd.cmds = NULL;
	data->_stdin = 4;
	data->_stdout = 5;
	data->deco = NULL;
	data->_stdin = dup2(STDIN_FILENO, data->_stdin);
	data->_stdout = dup2(STDOUT_FILENO, data->_stdout);
	g_sig_error_code = 0;
	init_data2(data);
}
