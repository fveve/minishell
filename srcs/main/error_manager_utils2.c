/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:28:05 by marvin            #+#    #+#             */
/*   Updated: 2024/06/13 15:36:08 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		verify_cmd(char	*input);

int		is_sep(char c, char *sep);

void	go_to_file(char *input_str, int *x, int *y);

int		verify_cmd4(char *input, int x, char **tab);

int	verify_quote2(char *input, int *x)
{
	(*x)++;
	while (input[*x] && input[*x] != '\'')
		(*x)++;
	if (!input[*x] || input[*x] != '\'')
	{
		printf("Quote need to be closed\n");
		return (1);
	}
	return (0);
}

int	verify_cmd2(char *input, int x)
{
	char	**tab;

	if (ft_countwords(input, "|;", &x) > 1)
		tab = ft_split(input, "|;", 1);
	else
	{
		tab = malloc(sizeof(char *) * 2);
		tab[0] = ft_strdup(input);
		tab[1] = NULL;
	}
	tab = remove_space(tab);
	x = 0;
	while (tab[x])
	{
		if (!tab[x] || just_space(tab[x], 0))
		{
			free_tab(tab);
			return (1);
		}
		x++;
	}
	if (verify_cmd4(input, x, tab))
		return (1);
	return (0);
}

int	is_in_quote2(const char *input, char *c)
{
	int	trigger;
	int	x;

	x = 0;
	trigger = 0;
	while (input[x])
	{
		if (is_sep(input[x], c))
			trigger = 1;
		if (input[x] == '\'' && !trigger)
		{
			x++;
			while (input[x] && input[x] != '\'')
			{
				if (is_sep(input[x], c))
					return (1);
				x++;
			}
		}
		else
			x++;
	}
	return (0);
}

int	is_in_quote3(const char *input, char *c)
{
	int	trigger;
	int	x;

	x = 0;
	trigger = 0;
	while (input[x])
	{
		if (is_sep(input[x], c))
			trigger = 1;
		if (input[x] == '\"' && !trigger)
		{
			x++;
			while (input[x] && input[x] != '\"')
			{
				if (is_sep(input[x], c))
					return (1);
				x++;
			}
		}
		else
			x++;
	}
	return (0);
}

void	go_to_file3(char *input_str, int *x, int *y)
{
	int	trigger;

	trigger = -1;
	while (input_str[*x])
	{
		if (input_str[*x] == '>')
			trigger++;
		(*x)++;
	}
	*x = 0;
	while (input_str[*x])
	{
		if (input_str[*x] == '>' && trigger)
			trigger--;
		else if (input_str[*x] == '>' && !trigger)
		{
			go_to_file(input_str, y, x);
			return ;
		}
		(*x)++;
	}
}
