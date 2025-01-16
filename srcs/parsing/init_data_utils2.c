/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:48:14 by arafa             #+#    #+#             */
/*   Updated: 2024/06/11 14:45:17 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_redirection2(char *input_str, int trigger);

int	is_redirection(char *input_str)
{
	int	x;

	x = 0;
	while (input_str[x])
	{
		skip_comma(input_str, &x);
		if (input_str[x] == '>' || input_str[x] == '<')
			return (1);
		if (!input_str[x])
			return (0);
		x++;
	}
	return (0);
}

int	n_o_r(char *input_str)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (input_str[x])
	{
		if (input_str[x] == '>' && input_str[x + 1] != '>')
			i++;
		x++;
	}
	return (i);
}

int	n_i_r(char *input_str)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (input_str[x])
	{
		if (input_str[x] == '<' && input_str[x + 1] != '<')
			i++;
		x++;
	}
	return (i);
}

char	*set_new_str(char *input)
{
	char	*new_str;

	new_str = ft_strdup(input);
	new_str = remove_redirection2(new_str, 0);
	new_str = remove_redirection2(new_str, 1);
	return (new_str);
}

int	set_i(char *input_str, int trigger)
{
	int	i;

	i = 0;
	if (!trigger)
		i = n_i_r(input_str);
	else if (trigger)
		i = n_o_r(input_str);
	return (i);
}
