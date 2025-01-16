/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:46:35 by leoherna          #+#    #+#             */
/*   Updated: 2024/02/27 11:46:35 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_quote3(const char *input, char *c);

int	is_in_quote2(const char *input, char *c);

void	ft_put_str(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		write(1, &str[x], 1);
		x++;
	}
}

int	nb_args(char **args)
{
	int		i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	print_it(char **args, int i)
{
	while (args[i])
	{
		ft_put_str(args[i]);
		if ((nb_args(args) - 1) > i)
			ft_put_str(" ");
		i++;
	}
	return (i);
}

int	echo_cmd(char *command)
{
	int		i;
	int		option_n;
	char	**args;

	args = ft_split(command, " ", 0);
	i = 1;
	option_n = 0;
	if (nb_args(args) > 1)
	{
		if (ft_strncmp(args[1], "-n", 2) == 0)
		{
			while (check_tiret_n(args[i], &option_n) == 0)
			{
				i++;
				if (args[i] == NULL)
					return (free_tab(args), 0);
			}
			option_n = 1;
		}
		i = print_it(args, i);
	}
	if (option_n != 1)
		printf("\n");
	return (free_tab(args), 0);
}
