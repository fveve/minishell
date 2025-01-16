/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:18:39 by arafa             #+#    #+#             */
/*   Updated: 2024/05/14 17:41:37 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**return_new_export_env(t_mini *mini, char *new_env_var);

static	char	**return_new_env(t_mini *mini, char *new_env_var)
{
	char	*env_one_line;
	char	*temp;
	int		i;

	i = 1;
	env_one_line = ft_strjoin(mini->env[0], " ");
	while (i != ft_strlen2(mini->env))
	{
		temp = ft_strjoin(env_one_line, " ");
		free(env_one_line);
		env_one_line = ft_strjoin(temp, mini->env[i]);
		free(temp);
		i++;
	}
	temp = ft_strjoin(env_one_line, " ");
	free(env_one_line);
	env_one_line = ft_strjoin(temp, new_env_var);
	free(temp);
	return (free_export_unset(env_one_line));
}

char	*defined_arg(char *line)
{
	char	*new_line;
	int		i;

	new_line = malloc(sizeof (char) * ((ft_strlen(line) + 1)));
	i = 0;
	while (line[i] != '\0')
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

char	*undefined_arg(char *line)
{
	char	*new_line;
	int		i;

	new_line = malloc(sizeof (char) * (ft_strlen(line) + 1));
	i = 0;
	while (line[i] != '\0')
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

int	check_values(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '=')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	**add_env_variable(t_mini *mini, char *new_env_var)
{
	char	**new_env;
	char	*new_line;

	if (check_values(new_env_var) == 1)
	{
		new_line = defined_arg(new_env_var);
		new_env = return_new_env(mini, new_line);
	}
	else
	{
		new_line = undefined_arg(new_env_var);
		new_env = return_new_export_env(mini, new_line);
	}
	free(new_line);
	return (new_env);
}
