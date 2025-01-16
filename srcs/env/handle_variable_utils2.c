/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variable_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:41:11 by arafa             #+#    #+#             */
/*   Updated: 2024/06/11 15:14:59 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_len_before_dollar(char *str);

int		get_varlen(char *command);

char	remove_dollar_input3(char *input_str, int *i, int *j);

char	*remove_dollar_input2(char	*input_str, char *variable, int *i, int *j)
{
	int		k;
	char	*temp;
	char	*new_input;

	k = 0;
	new_input = NULL;
	temp = malloc(sizeof(char) * (get_len_before_dollar(input_str) + 1));
	while (input_str[*i] != '\0')
	{
		if (input_str[*i] == '$' && k == 0)
		{
			temp[*j] = '\0';
			new_input = ft_strdup(temp);
			while (input_str[*i] && variable[k] && input_str[*i] == variable[k])
			{
				(*i)++;
				k++;
			}
			free(temp);
			*j = 0;
			break ;
		}
		temp[*j] = remove_dollar_input3(input_str, i, j);
	}
	return (new_input);
}

void	change_input_str_utils(t_mini *mini, char **variable, char **input_str)
{
	int		which_line;
	char	*value;

	which_line = check_if_exist_handle(mini, *variable);
	if (which_line != -1)
	{
		value = search_value(mini, which_line);
		edit_input_str(input_str, value, *variable);
		free(value);
	}
	else
		remove_dollar_input(input_str, *variable);
	free(*variable);
	*variable = variable_taker(*input_str);
}

void	change_input_str(t_mini *mini, char **input_str)
{
	char	*variable;
	char	*value;

	variable = NULL;
	if (*input_str == NULL)
		return ;
	add_history(*input_str);
	variable = variable_taker(*input_str);
	if (variable == NULL)
		return ;
	while (ft_strncmp(variable, "?", ft_strlen(variable)) == 0)
	{
		value = ft_itoa(g_sig_error_code);
		edit_input_str(input_str, value, variable);
		free(value);
		free(variable);
		variable = variable_taker(*input_str);
		if (variable == NULL)
			return ;
	}
	while (variable != NULL)
		change_input_str_utils(mini, &variable, input_str);
	free(variable);
}

char	remove_dollar_input3(char *input_str, int *i, int *j)
{
	(*j)++;
	return ((*i)++, input_str[*i]);
}
