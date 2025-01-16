/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:01:14 by leoherna          #+#    #+#             */
/*   Updated: 2024/06/13 15:14:31 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_res_stdinfileno;
int	g_sig_error_code;

int	main(int argc, char **argv, char **env)
{
	int		original_stdin;
	t_data	data;

	(void)argc;
	(void)argv;
	init_data(&data, env);
	init_cmd(&data.cmd, "");
	free_cmd(&data.cmd);
	change_shell_level(&data.mini.env);
	change_shell_level(&data.mini.export_env);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	loop(&data, &original_stdin);
	return (0);
}
