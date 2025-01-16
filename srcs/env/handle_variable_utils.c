/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variable_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:28:45 by arafa             #+#    #+#             */
/*   Updated: 2024/06/11 15:15:21 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_if_exist_handle(t_mini *mini, char *variable);

char	*search_value(t_mini *mini, int j);

char	*remove_dollar_input2(char	*input_str, char *variable, int *i, int *j);

int	get_len_before_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (0);
}

void	remove_dollar_input_utils(t_tools *tools,
	char *variable, char **input_str)
{
	while ((*input_str)[tools->i] != '\0')
	{
		if ((*input_str)[tools->i] == '$')
		{
			tools->temp[tools->j] = '\0';
			tools->new_input = ft_strdup(tools->temp);
			tools->i++;
			while (((*input_str)[tools->i] && variable[tools->k]) &&
				(*input_str)[tools->i] == variable[tools->k])
			{
				tools->i++;
				tools->k++;
			}
			free(tools->temp);
			tools->j = 0;
			break ;
		}
		tools->temp[tools->j] = (*input_str)[tools->i];
		tools->j++;
		tools->i++;
	}
	tools->temp = malloc(sizeof(char) * ((ft_strlen(*input_str))
				- (get_len_before_dollar(*input_str)
					+ ft_strlen(variable) + 1) + 1));
}

void	remove_dollar_input(char	**input_str, char *variable)
{
	t_tools	tools;

	tools.k = 0;
	tools.j = 0;
	tools.i = 0;
	tools.temp = malloc(sizeof(char) * (get_len_before_dollar(*input_str) + 1));
	remove_dollar_input_utils(&tools, variable, input_str);
	while ((*input_str)[tools.i] != '\0')
	{
		tools.temp[tools.j] = (*input_str)[tools.i];
		tools.j++;
		tools.i++;
	}
	tools.temp[tools.j] = '\0';
	free(*input_str);
	if (tools.temp[0])
		*input_str = ft_strjoin(tools.new_input, tools.temp);
	else
		*input_str = ft_strdup(tools.new_input);
	if (tools.temp)
		free(tools.temp);
	free(tools.new_input);
}

void	edit_input_str_utils(t_tools *tools,
	char *variable, char *value, char **input_str)
{
	while ((*input_str)[tools->i] != '\0')
	{
		if ((*input_str)[tools->i] == '$')
		{
			tools->temp[tools->j] = '\0';
			tools->new_input = ft_strjoin(tools->temp, value);
			tools->i++;
			while (((*input_str)[tools->i] && variable[tools->k])
				&& (*input_str)[tools->i] == variable[tools->k])
			{
				tools->i++;
				tools->k++;
			}
			free(tools->temp);
			tools->j = 0;
			break ;
		}
		tools->temp[tools->j] = (*input_str)[tools->i];
		tools->j++;
		tools->i++;
	}
	tools->temp = malloc(sizeof(char) * (ft_strlen(value)
				+ (ft_strlen(*input_str)) - (get_len_before_dollar(*input_str)
					+ ft_strlen(variable) + 1) + 1));
}

void	edit_input_str(char	**input_str, char *value, char *variable)
{
	t_tools	tools;

	tools.k = 0;
	tools.j = 0;
	tools.i = 0;
	tools.temp = malloc(sizeof(char)
			* (get_len_before_dollar(*input_str) + 1));
	edit_input_str_utils(&tools, variable, value, input_str);
	while ((*input_str)[tools.i] != '\0')
	{
		tools.temp[tools.j] = (*input_str)[tools.i];
		tools.j++;
		tools.i++;
	}
	tools.temp[tools.j] = '\0';
	free(*input_str);
	if (tools.temp[0])
		*input_str = ft_strjoin(tools.new_input, tools.temp);
	else
		*input_str = ft_strdup(tools.new_input);
	if (tools.temp)
		free(tools.temp);
	free(tools.new_input);
}
