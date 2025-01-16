/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:25:00 by leoherna          #+#    #+#             */
/*   Updated: 2024/02/27 10:25:00 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_env_cmd(t_mini *mini)
{
	int	j;

	j = 0;
	while (mini->export_env[j] != NULL)
	{
		printf("declare -x ");
		printf("%s\n", mini->export_env[j]);
		j++;
	}
}

void	env_cmd(t_mini *mini)
{
	int	j;

	j = 0;
	while (mini->env[j] != NULL)
	{
		printf("%s\n", mini->env[j]);
		j++;
	}
}
