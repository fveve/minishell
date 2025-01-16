/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:51:58 by leoherna          #+#    #+#             */
/*   Updated: 2024/04/22 11:51:58 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home(t_mini *mini)
{
	int		i;
	int		j;
	char	*path;

	path = NULL;
	i = 5;
	j = 0;
	if (mini->env[j] == NULL)
		return (path);
	while (ft_strncmp("HOME", mini->env[j], 4) || mini->env[j] == NULL)
		j++;
	if (mini->env[j] == NULL)
		return (path);
	path = malloc(sizeof(char) * (ft_strlen(mini->env[j]) - 4));
	while (i != ft_strlen(mini->env[j]))
	{
		path[i - 5] = mini->env[j][i];
		i++;
	}
	path[i - 5] = '\0';
	return (path);
}

char	*get_oldpwd(t_mini *mini)
{
	int		i;
	int		j;
	char	*path;

	path = NULL;
	i = 7;
	j = 0;
	while (mini->env[j] && ft_strncmp("OLDPWD", mini->env[j], 6))
		j++;
	if (mini->env[j] == NULL)
		return (path);
	path = malloc(sizeof(char) * (ft_strlen(mini->env[j]) - 6));
	while (i != ft_strlen(mini->env[j]))
	{
		path[i - 7] = mini->env[j][i];
		i++;
	}
	path[i - 7] = '\0';
	return (path);
}

char	*get_env_path(t_mini *mini, int option)
{
	char	*home;
	char	*oldpwd;

	home = get_home(mini);
	oldpwd = get_oldpwd(mini);
	if (option == 1)
	{
		free(home);
		return (oldpwd);
	}
	else
	{
		free(oldpwd);
		return (home);
	}
}

int	ft_error(int which_error)
{
	if (which_error == 0)
	{
		g_sig_error_code = 126;
		printf("No access to directory\n");
		return (0);
	}
	return (1);
}

int	dir_access(char **path)
{
	if (access(path[2], F_OK | X_OK) != -1)
		return (1);
	else
		return (0);
}
