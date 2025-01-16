/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:25:35 by leoherna          #+#    #+#             */
/*   Updated: 2024/02/26 12:25:35 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	update_export_env2(t_mini *mini)
{
	int		i;
	char	current_dir[1024];

	i = 0;
	if (mini->export_env == NULL)
		return ;
	while (mini->export_env[i])
	{
		if (ft_strncmp(mini->export_env[i], "PWD", 3) != 0)
			break ;
		i++;
	}
	if (mini->export_env[i] == NULL)
		return ;
	getcwd(current_dir, 1024);
	free(mini->export_env[i]);
	mini->export_env[i] = ft_strjoin("PWD=", current_dir);
}

void	update_env2(t_mini *mini)
{
	int		i;
	char	current_dir[1024];

	i = 0;
	if (mini->env == NULL)
		return ;
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], "PWD", 3) != 0)
			break ;
		i++;
	}
	if (mini->env[i] == NULL)
		return ;
	getcwd(current_dir, 1024);
	free(mini->env[i]);
	mini->env[i] = ft_strjoin("PWD=", current_dir);
	update_export_env2(mini);
}

int	pwd_cmd(void)
{
	char	current_dir[1024];

	if (getcwd(current_dir, 1024))
	{
		printf("%s\n", current_dir);
		return (1);
	}
	else
		return (0);
}
