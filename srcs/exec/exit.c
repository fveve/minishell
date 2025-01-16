/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:27:53 by leoherna          #+#    #+#             */
/*   Updated: 2024/06/13 15:23:51 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_allminidebug(t_mini *mini)
{
	it_works(mini->env);
	printf("\n\nexport env : \n\n\n");
	it_works(mini->export_env);
}

int	check_input(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] > '9' || input[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

void	exit_with_value(t_data *data, char **command, char *input_str)
{
	int		exit_value;

	exit_value = 0;
	free_cmd(&data->cmd);
	if (check_input(command[1]) == 1)
	{
		exit_value = ft_atoi(command[1]);
		free_mini(&data->mini);
		free_tab(command);
		free(input_str);
		exit(exit_value);
	}
	printf("minishell: exit: %s: numeric argument required\n", command[1]);
	free_mini(&data->mini);
	free_tab(command);
	if (input_str)
		free(input_str);
	exit(0);
}

int	exit_manager(t_data *data, char *input_str)
{
	char	**command;

	command = ft_split(input_str, " ", 0);
	if (ft_strlen2(command) == 2)
		exit_with_value(data, command, input_str);
	else if (ft_strlen2(command) == 1)
	{
		if (input_str
			&& ft_strncmp(data->cmd.input_str, input_str, ft_strlen(input_str)))
			free(input_str);
		free_cmd(&data->cmd);
		free_mini(&data->mini);
		if (command)
			free_tab(command);
		exit(g_sig_error_code);
	}
	else if (ft_strlen2(command) == 0)
	{
		free_mini(&data->mini);
		exit(g_sig_error_code);
	}
	if (command)
		free_tab(command);
	return (0);
}
