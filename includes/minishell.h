/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:01:33 by leoherna          #+#    #+#             */
/*   Updated: 2024/02/21 14:01:33 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include <fcntl.h>
# include "pipex.h"

extern int	g_res_stdinfileno;
extern int	g_sig_error_code;

/*------------------------SRCS/BUILTINS/PWD---------------------------*/
int		pwd_cmd(void);
int		cd_cmd(t_mini *mini, char *cmd);
void	ls_cmd(char *cmd);
int		echo_cmd(char *cmd);
void	env_cmd(t_mini *mini);
void	export_env_cmd(t_mini *mini);
void	unset_cmd(t_mini *mini, char *cmd);
void	dollar_cmd(t_data *data);
void	export_cmd(t_mini *mini, char *cmd);

/*------------------------SRCS/ENV/EXPORT_UTILS---------------------*/
char	**alpha_reorder(char **env);
char	**add_env_variable(t_mini *mini, char *new_env_var);
int		check_if_exist_export(char **given_env, char *variable);
int		does_var_exist(t_mini *mini, char *env_to_remove);
char	**get_env_one_line_export(t_mini *mini, char *env_to_remove);
void	change_export_env(t_mini *mini, char **almostnewenv);
void	change_shell_level(char	***env);

/*-------------------this one is on unset cmd and his utils-----*/
void	remove_export_variable(t_mini *mini, char **command, int i);
void	handle_here_doc(t_data *data, char *word);
char	**get_env_one_line_unset(t_mini *mini, char *env_to_remove);
int		check_if_exist_export(char **given_env, char *variable);
void	remove_export_variable_unset(t_mini *mini, char **command, int i);
char	**get_export_env_one_line_unset(t_mini *mini, char *env_to_remove);
int		does_var_exist2(t_mini *mini, char *env_to_remove);

/*-------------------SRCS/ENV/HANDLE_VARIABLE---------------------*/
int		get_varlen(char *command);
int		get_varlen(char *command);
int		check_if_exist_handle(t_mini *mini, char *variable);
char	*variable_taker(char *command);
char	*search_value(t_mini *mini, int j);
void	init_logname(t_mini *mini);
char	*dollar_found(int i, int j, char *command, char *variable);
void	init_logname(t_mini *mini);
void	change_input_str(t_mini *mini, char **input_str);
void	edit_input_str(char	**input_str, char *value, char *variable);
void	remove_dollar_input(char	**input_str, char *variable);

/*-----------------------SRCS/ENV/CD_UTILS2----------------------*/
void	cd_utils2(t_mini *mini, char *second_path);
int		help_for_cd(t_mini *mini, char **command, char *path);
int		cd_alone(t_mini *mini, char *path);
int		cd_wave(t_mini *mini, char **command, char *path);
int		dir_access(char **path);
int		ft_error(int which_error);
char	*get_home(t_mini *mini);
char	*get_oldpwd(t_mini *mini);
char	*get_env_path(t_mini *mini, int option);
void	update_env2(t_mini *mini);
int		help_for_cd(t_mini *mini, char **command, char *path);

/*-----------------------SRCS/ENV/EXPORT_UTILS2------------------*/
void	defined_function(t_mini *mini, char **command, int i);
void	undefined_function(t_mini *mini, char **command, int i);

/*------------------------------PARSING--------------------------*/
char	*set_new_str(char *input);
char	**remove_space(char **cmd);
char	*set_input(char	*input_str, int *x);
int		n_o_r(char *input_str);
int		n_i_r(char *input_str);
int		just_space(char	*str, int y);
int		is_command(char *str, int x);
int		is_pipes(t_cmd *cmd, char *str);
int		is_redirection(char *input_str);
int		set_i(char *input_str, int trigger);

/*----------------------------PIPEX_UTILS-----------------------*/
int		is_slash(char	*str);
int		ft_countwords(char const *s, char *c, int *trig_cote);
char	**set_tab(char *cmd);
char	**remove_space(char **cmd);
char	*set_path(t_data *data, char *tab);
char	*find_path(char *cmd, char **env);
void	set_parent(t_data *data, int pid, int pipe_fd[2]);

/*-------------------------SRCS/EXEC/EXEC-----------------------*/
void	exec(t_data *data);

/*---------------------SRCS/EXEC/EXIT---------------------------*/
int		exit_manager(t_data *data, char *input_str);

/*------------------------SRCS/PARSING-------------------------*/
void	init_data(t_data *data, char **env);
void	init_mini(t_mini *mini, char **env);
void	init_mini2(t_mini *mini, char **env);
void	init_cmd(t_cmd *cmd, char *input_str);

/*-------------------------- SRCS/MAIN/MANAGER----------------*/
void	loop(t_data *data, int *original_stdin);
void	new_cwd(t_data *data);
char	*set_deco(t_data *data);

/*----------------------SRCS/MAIN/SIGNAL----------------------*/
void	handle_signal(int sig);

/*------------HANDLE PIPE/REDIRECTION/APPEND------------------*/
void	pipex(t_data *data);

/*----------------------SRCS/TOOLS/FREE_UTILS-----------------*/
void	free_tab(char **tab);
void	free_cmd(t_cmd *cmd);
char	**free_export_unset(char *env_one_line);
void	free_mini(t_mini *mini);

/*--------------------SRCS/TOOLS/FT_SPLIT--------------------*/
char	**ft_split(char *s, char *c, int bol_quote);
char	*ft_itoa(int nb);

/*--------------srcs/TOOLS/LIBUTILS-------------------------*/
int		ft_atoi( char *nptr);
int		ft_strncmp(const char *s1, const char *s2, size_t size);
int		ft_strlen(const char *str);
int		ft_strlen2(char **tab);
int		ft_strlen_equal(char *str);
int		is_printable(char c);
int		is_in_quote(const char *input, char *c, int y);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *src);
char	*ft_strdup_equal(char *src);
void	ft_putstr_fd(int fd, char *str);
void	skip_comma(char *input, int *x);
int		check_tiret_n(char *str, int *option_n);

/*--------------------DEBUG---------------------------------*/
void	it_works(char **tab);

#endif