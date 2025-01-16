/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:33:52 by leoherna          #+#    #+#             */
/*   Updated: 2024/04/05 12:33:52 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**return_new_export_env(t_mini *mini, char *new_env_var);

void	defined_function2(t_mini *mini, char **command, int i);

void	defined_function2(t_mini *mini, char **command, int i);

char	**get_export_env_one_line_unset2(t_mini *mini, char *env_to_remove);

int	check_if_exist(char **given_env, char *variable)
{
	int	j;

	j = 0;
	while (given_env[j])
	{
		if (ft_strncmp(given_env[j], variable, ft_strlen_equal(variable)) == 0)
		{
			return (1);
		}
		j++;
	}
	return (-1);
}

void	change_env(t_mini *mini, char **almostnewenv)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = alpha_reorder(almostnewenv);
	free_tab(mini->env);
	mini->env = malloc(sizeof(char *) * (ft_strlen2(new_env) + 1));
	while (new_env[j] != NULL)
	{
		mini->env[j] = malloc (sizeof(char) * (ft_strlen(new_env[j]) + 1));
		while (new_env[j][i] != '\0')
		{
			mini->env[j][i] = new_env[j][i];
			i++;
		}
		mini->env[j][i] = '\0';
		i = 0;
		j++;
	}
	mini->env[j] = NULL;
	free_tab(new_env);
}

void	already_defined(t_mini *mini, char **commands, int i)
{
	char	*new_env_var;
	char	**new_env;
	char	**new_export_env;

	new_env_var = ft_strdup_equal(commands[i]);
	new_env = get_env_one_line_unset(mini, new_env_var);
	change_env(mini, new_env);
	new_export_env = get_export_env_one_line_unset2(mini, new_env_var);
	change_export_env(mini, new_export_env);
	free(new_env_var);
	free_tab(new_env);
	free_tab(new_export_env);
}

void	defined_function(t_mini *mini, char **command, int i)
{
	char	**new_env;
	char	**new_export_env;

	new_export_env = NULL;
	new_env = NULL;
	if (check_if_exist_export(mini->export_env, command[i]) == 1
		&& check_if_exist(mini->env, command[i]) == -1)
	{
		new_env = add_env_variable(mini, command[i]);
		change_env(mini, new_env);
		remove_export_variable(mini, command, i);
		new_export_env = return_new_export_env(mini, command[i]);
		change_export_env(mini, new_export_env);
	}
	else if (check_if_exist(mini->env, command[i]) == -1)
	{
		new_env = add_env_variable(mini, command[i]);
		change_env(mini, new_env);
		new_export_env = return_new_export_env(mini, command[i]);
		change_export_env(mini, new_export_env);
	}
	else if (check_if_exist(mini->env, command[i]) == 1)
		defined_function2(mini, command, i);
	free_tab(new_env);
	free_tab(new_export_env);
}

void	undefined_function(t_mini *mini, char **command, int i)
{
	char	**new_env;

	new_env = add_env_variable(mini, command[i]);
	if (check_if_exist(mini->env, command[i]) == -1
		&& check_if_exist(mini->export_env, command[i]) == -1)
		change_export_env(mini, new_env);
	free_tab(new_env);
}
