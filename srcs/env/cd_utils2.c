/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:06:31 by leoherna          #+#    #+#             */
/*   Updated: 2024/05/16 14:06:31 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	help_for_cd(t_mini *mini, char **command, char *path)
{
	int		i;
	int		j;
	char	*second_path;

	j = 0;
	i = 1;
	if (chdir(path) != 0)
	{
		g_sig_error_code = 1;
		printf("Erreur lors du changement de répertoire\n");
	}
	if (ft_strlen(command[1]) == 1)
		return (1);
	free(path);
	second_path = malloc(sizeof(char) * ft_strlen(command[1]));
	while (command[1][i] != '\0')
	{
		i++;
		second_path[j] = command[1][i];
		j++;
	}
	second_path[j] = '\0';
	cd_utils2(mini, second_path);
	return (1);
}

int	cd_wave(t_mini *mini, char **command, char *path)
{
	char	*temp;

	temp = NULL;
	temp = get_env_path(mini, 2);
	if (temp == NULL)
	{
		printf("bash: cd: HOME not set\n");
		g_sig_error_code = 1;
		return (0);
	}
	path = ft_strdup(temp);
	free(temp);
	help_for_cd(mini, command, path);
	free(path);
	return (1);
}

int	cd_alone(t_mini *mini, char *path)
{
	char	*temp;

	temp = NULL;
	temp = get_env_path(mini, 2);
	if (temp == NULL)
	{
		printf("bash: cd: HOME not set\n");
		g_sig_error_code = 1;
		return (0);
	}
	path = ft_strdup(temp);
	free(temp);
	if (chdir(path) != 0)
	{
		g_sig_error_code = 1;
		printf("Erreur lors du changement de répertoire\n");
	}
	free(path);
	return (1);
}

void	cd_utils2(t_mini *mini, char *second_path)
{
	if (chdir(second_path) != 0)
	{
		g_sig_error_code = 1;
		printf("Erreur lors du changement de répertoire\n");
		if (chdir(mini->cwd) != 0)
		{
			g_sig_error_code = 1;
			printf("Erreur lors du changement de répertoire\n");
		}
	}
	free(second_path);
}
