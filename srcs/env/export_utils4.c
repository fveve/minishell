/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:24:00 by leoherna          #+#    #+#             */
/*   Updated: 2024/05/14 17:24:00 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_export_env(t_mini *mini, char **almostnewenv)
{
	int		i;
	int		j;
	char	**new_env;

	new_env = alpha_reorder(almostnewenv);
	i = 0;
	j = 0;
	free_tab(mini->export_env);
	mini->export_env = malloc(sizeof(char *) * (ft_strlen2(new_env) + 1));
	while (new_env[j] != NULL)
	{
		mini->export_env[j]
			= malloc(sizeof(char) * (ft_strlen(new_env[j]) + 1));
		while (new_env[j][i] != '\0')
		{
			mini->export_env[j][i] = new_env[j][i];
			i++;
		}
		mini->export_env[j][i] = '\0';
		i = 0;
		j++;
	}
	mini->export_env[j] = NULL;
	free_tab(new_env);
}

int	check_if_exist_export(char **given_env, char *variable)
{
	int	j;

	j = 0;
	while (given_env[j])
	{
		if (ft_strncmp(given_env[j], variable, ft_strlen(given_env[j])) == 0)
		{
			return (1);
		}
		j++;
	}
	return (-1);
}

char	**get_env_one_line_export(t_mini *mini, char *env_to_remove)
{
	char	*env_one_line;
	char	*temp;
	int		i;

	i = 1;
	env_one_line = ft_strjoin(mini->export_env[0], " ");
	while (i != ft_strlen2(mini->export_env))
	{
		if (ft_strncmp(mini->export_env[i], env_to_remove,
				ft_strlen(mini->export_env[i])) == 0)
			i++;
		else
		{
			temp = ft_strjoin(env_one_line, " ");
			free(env_one_line);
			env_one_line = ft_strjoin(temp, mini->export_env[i]);
			free(temp);
			i++;
		}
	}
	return (free_export_unset(env_one_line));
}

void	remove_export_variable_defined(t_mini *mini, char **command, int i)
{
	char	**new_env;

	if (does_var_exist(mini, command[i]) == 1)
	{
		new_env = get_env_one_line_export(mini, command[i]);
		change_export_env(mini, new_env);
		free_tab(new_env);
	}
}

void	remove_export_variable(t_mini *mini, char **command, int i)
{
	char	**new_env;

	if (does_var_exist(mini, command[i]) == 1)
	{
		new_env = get_env_one_line_export(mini, command[i]);
		change_export_env(mini, new_env);
		free_tab(new_env);
	}
}
