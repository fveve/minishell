/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager_utils3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 02:28:42 by marvin            #+#    #+#             */
/*   Updated: 2024/06/13 15:50:38 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify_redirection5(char *input, int trigger, int x);

int	is_comma(char *input)
{
	int	x;

	x = 0;
	while (input[x])
	{
		skip_comma(input, &x);
		if (input[x] == ';')
			return (1);
		x++;
	}
	return (0);
}

int	is_only_comma(char *input)
{
	int	x;

	x = 0;
	while (input[x])
	{
		if (input[x] != ' ' && input[x] != '	' && input[x] != ';')
			return (0);
		x++;
	}
	return (1);
}

int	ft_str_pipe(char *input)
{
	int	x;
	int	pipe;

	x = 0;
	pipe = 0;
	while (input[x])
	{
		skip_comma(input, &x);
		if (input[x] == '|')
			pipe++;
		x++;
	}
	return (pipe);
}

int	verify_pipe(char *input)
{
	char	**temp;
	int		x;

	temp = ft_split(input, "|;", 1);
	remove_space(temp);
	x = 0;
	while (temp[x])
	{
		if (!temp[x][0] || just_space(temp[x], 0)
			|| is_only_comma(temp[x])
			|| ft_str_pipe(input) + 1 != ft_strlen2(temp))
		{
			free_tab(temp);
			return (1);
		}
		x++;
	}
	free_tab(temp);
	if (x == 0)
		return (1);
	return (0);
}

int	verify_redirection4(char *input)
{
	char	**temp;
	int		x;
	int		trigger;

	x = 0;
	temp = ft_split(input, "<>", 1);
	while (temp[x])
	{
		if (just_space(temp[x], 0) && x != 0)
		{
			printf("Redirection problem\n");
			free_tab(temp);
			return (1);
		}
		x++;
	}
	free_tab(temp);
	trigger = 0;
	if (verify_redirection5(input, trigger, x))
		return (1);
	return (0);
}
