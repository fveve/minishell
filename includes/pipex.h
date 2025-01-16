/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:10:20 by arafa             #+#    #+#             */
/*   Updated: 2023/12/22 11:44:15 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "minishell.h"

//Structure-------------------------------------------------
typedef struct s_tools
{
	int		i;
	int		j;
	int		k;
	char	*temp;
	char	*new_input;
}				t_tools;

typedef struct s_mini
{
	char	*logname;
	char	**env;
	char	**export_env;
	char	*cwd;
	int		error_code;
}	t_mini;

typedef struct s_cmd
{
	char	**cmds;
	char	*input_str;
	int		is_pipe;
	int		pipes;
	int		trigger;
}	t_cmd;

typedef struct s_data
{
	int		_stdin;
	int		_stdout;
	int		index;
	int		index_trigger;
	int		fd[1000][2];
	char	*deco;
	t_cmd	cmd;
	t_mini	mini;
}	t_data;

//Functions-------------------------------------------------
int		is_tiret(char *s);
int		is_file(char *s);
int		is_path(char *s);
char	*ft_substr(char const *s, int start, int len);
char	**extract_args(char **argv, int x);
void	ft_check_args(int argc, char **argv, char **env, t_data *data);
void	exec_child(t_data *data, int x);
void	free_tab(char **tab);
#endif