/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:05:20 by leoherna          #+#    #+#             */
/*   Updated: 2024/06/13 15:25:18 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_mini(t_mini *mini)
{
	if (mini->env)
		free_tab(mini->env);
	if (mini->export_env)
		free_tab(mini->export_env);
	if (mini->cwd)
		free(mini->cwd);
	if (mini->logname)
		free(mini->logname);
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->cmds)
		free_tab(cmd->cmds);
	if (cmd->input_str)
		free(cmd->input_str);
}

char	**free_export_unset(char *env_one_line)
{
	char	**new_env;

	new_env = ft_split(env_one_line, " ", 1);
	free(env_one_line);
	return (new_env);
}
