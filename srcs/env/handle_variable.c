/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:19:31 by leoherna          #+#    #+#             */
/*   Updated: 2024/02/27 13:19:31 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_len_before_dollar(char *str);

int		get_varlen(char *command);

char	remove_dollar_input3(char *input_str, int *i, int *j);

char	*remove_dollar_input2(char	*input_str, char *variable, int *i, int *j);

char	*variable_taker(char *command)
{
	int		i;
	int		j;
	char	*variable;

	variable = NULL;
	i = 0;
	j = 0;
	if (!command)
		return (NULL);
	while (command[i] != '\0')
	{
		if (command[i] == '\'')
		{
			i++;
			while (command[i] != '\'' && command[i] != '\0')
				i++;
		}
		if (command[i] == '$')
			return (dollar_found(i, j, command, variable));
		if (!command[i])
			break ;
		i++;
	}
	return (variable);
}

int	ft_strlen_handle(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

int	check_if_exist_handle(t_mini *mini, char *variable)
{
	int	j;

	j = 0;
	while (mini->env[j] != NULL)
	{
		if (ft_strncmp(mini->env[j], variable,
				ft_strlen_handle(mini->env[j])) == 0)
			return (j);
		j++;
	}
	return (-1);
}

char	*search_value(t_mini *mini, int j)
{
	int		i;
	int		ii;
	char	*to_print;

	i = 0;
	ii = 0;
	while (mini->env[j][i] != '=')
		i++;
	i++;
	while (mini->env[j][i] != '\0')
	{
		ii++;
		i++;
	}
	i = i - ii;
	to_print = malloc(sizeof(char) * (ii + 1));
	ii = 0;
	while (mini->env[j][i] != '\0')
	{
		to_print[ii] = mini->env[j][i];
		ii++;
		i++;
	}
	to_print[ii] = '\0';
	return (to_print);
}

void	dollar_cmd(t_data *data)
{
	(void)(data);
}
