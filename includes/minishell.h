/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperea-d <pperea-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 18:26:55 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/03 04:14:57 by pperea-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define READ_END	0    /* index pipe extremo escritura */
# define WRITE_END	1    /* index pipe extremo lectura */

# define YELLOW "\033[1;33m"
# define GREEN  "\033[1;32m"
# define BLUE   "\033[1;34m"
# define PINK   "\033[1;35m"
# define GRAY   "\033[1;30m"
# define CYAN   "\033[1;36m"
# define RED    "\033[1;31m"
# define WHITE  "\033[0;37m"

typedef struct s_envs
{
	char			*name;
	char			*data;
	struct s_envs	*next;
}				t_envs;

typedef struct s_cmds
{
	char			*cmd;
	char			**str_pipe;
	char			***pipes;
	char			***file;
	int				**flag;
	int				num_pipes;
}				t_cmds;

typedef struct s_doble_pipes
{
	int				pipe;
	char			**doble_pipes;
	int				df;
	int				open_q;
	int				close_q;
}				t_doble_pipes;

typedef struct s_mini
{
	t_envs			*lista_envs;
	t_cmds			lista_cmds;
	char			**env_vars;
	int				numenv;
	int				num_pipes;
	char			*pathname;
	int				ret;
	char			*command;
	int				num_commands;
	int				sq;
	int				dq;
	int				open;
	int				close;
	int				export_equal;
	int				export_data_null;
	int				vars_ordered;
	int				error;
	t_doble_pipes	*double_pipes;
}				t_mini;

void			get_cmd(t_mini *mini);
void			split_cmd(t_mini *mini);
void			cmd_parse(t_mini *mini, t_cmds *lista_cmds, char *env[]);
void			prep_pipes(t_mini *mini);
void			check_cmd(t_mini *mini, char **cmd);
void			run_generic_cmd(t_mini *mini, char **cmd);
void			run_cmd_echo(t_mini *mini, char **cmd);
int				ft_numenv(char *env[]);
void			init_env(t_mini *mini, char *env[]);
void			searchpath(t_mini *mini);
void			prompt_msg(t_mini *mini);
void			save_env_vars(char *env[], t_mini *mini);
char			*set_value_env_var(char *mini_command, t_mini *mini);
int				run_cmd_pwd(t_mini *mini);
int				run_cmd_cd(t_mini *mini, char **cmd);
void			builtin_cd_points(t_mini *mini);
void			builtin_cd_absolute(t_mini *mini, char **cmds);
void			builtin_cd_relative(t_mini *mini, char **cmds);
void			update_old_path(t_mini *mini, char *cwd);
void			ft_exit(t_mini *mini, char **cmd);
void			run_cmd_env(t_mini *mini);
void			calc_num_cmds(t_mini *mini, t_cmds **lista_cmds);
void			nodo(t_envs **lista, char **vars);
void			add_nodo_cmd(t_cmds *nodo, t_cmds **lista_cmds);
char			**skip_doubleq(char **cmd);
char			**skip_simpleq(char **cmd);
void			calc_num_pipes(t_mini *mini);
void			split_cmd_nodos(t_mini *mini);
void			nodo_cmd(char **cmds);
void			skip_spaces(t_mini *mini);
void			delete_lista_cmds(t_cmds **lista_cmds);
void			delete_lista_cmds(t_cmds **lista_cmds);
void			free_str(char **str);
void			free_memory(t_mini *mini);
void			delete_lista(t_envs **lista);
void			nodos_manager(t_mini *mini);
void			get_redirection(t_mini *mini, int k, int num_f);
char			*simple_skip_spaces(char *file);
char			*char_to_str(char c);
void			env_in_array(t_mini *mini);
void			run_export(t_mini *mini, char *str);
void			execute_pipes(t_mini *mini);
void			init_pipes_cmd(t_mini *mini);
void			run_unset(t_mini *mini, char *str);
void			print_pipes(t_mini *mini);
int				check_builtin(char **cmd);
void			free_memory2(t_mini *mini);
void			check_sq_dq(char *cmd, t_mini *mini);
int				save_n_flag(char **cmd);
char			**set_env_vars(t_mini *mini, char **cmd);
char			*join_splitted_cmds(char **cmd, int n);
char			*builtin_cd_absolute_aux(t_mini *mini, char **cmds, char *pwd);
char			*builtin_cd_relative_aux(t_mini *mini, char *pwd);
char			*ft_strtrim_quotes(char *data);
char			*ft_strtrim_bar(char *data);
void			run_export_aux(t_mini *mini, char *str);
char			**manage_equal(char **aux, char *str);
char			**manage_data_null(char **aux, char *str);
void			print_ordered_env(t_mini *mini);
char			**manage_doubleq(char *str);
char			**manage_simpleq(char *str);
void			parse_export(t_mini *mini, char *str);
void			vars_loop(t_mini *mini, char **vars, int env_len);
char			**create_cmd(t_mini *mini, char **cmd, char *str);
void			run_minishell(char *cmd, t_mini *mini);
void			builtin_cd_home(t_mini *mini);
char			*builtin_cd_home_aux(t_mini *mini, char *pwd);
void			signals(void);
void			new_sig(int sig);
void			new_sig2(int sig);
char			*run_cmd_env_aux(char *data, char *name);
int				parse_existing_export(t_mini *mini, char **aux);
void			parse_expand_path(t_mini *mini, char **cmd);
char			**ft_double_files(t_mini *mini, char *str, int k);
void			free_str2(t_mini *mini);
int				flag_absolute(char *cmd);
void			free_matrix(t_mini *mini, char ***str);
void			free_tritrix(t_mini *mini);
void			free_int(t_mini *mini, int **flag);
int				get_redirection_flag1(t_mini *mini, int k, int j, int f);
int				get_redirection_flag0(t_mini *mini, int k, int j, int f);
int				get_redirection_flag2(t_mini *mini, int k, int j, int f);
int				get_redirection_flagminus1(t_mini *mini, int k, int j, int f);
void			get_double_files(t_mini *mini, int k, int f);
int				get_redirection_aux1(t_mini *mini, int j, int k, int f);
int				get_redirection_aux2(t_mini *mini, int j, int k, int f);
void			get_redirection_noquotes(t_mini *mini, int *j, int k, int *f);
void			get_redirection_quotes(t_mini *mini, int *j, int k, int *f);
void			ft_exit2(t_mini *mini);
void			get_pipes(t_mini *mini, int k);
void			position_comillas(t_mini *mini);
void			nodos_manager2(t_mini *mini);
void			calculate_pipes_s(t_mini *mini);
void			calculate_pipes_c(t_mini *mini);
int				calculate_pipes_c_before(t_mini *mini, int i, int p);
int				calculate_pipes_c_after(t_mini *mini, int i, int p);
int				num_files(char *str, t_mini *mini);
void			add_double_files(t_mini *mini, int i);
void			ft_exit(t_mini *mini, char **cmd);
void			ft_exc1(t_mini *mini);
void			ft_exc2(t_mini *mini, char **cmd, int e);
void			ft_exc3(t_mini *mini, char **cmd, int e);
int				count_exit(char **cmd);
int				ft_ismuldig(char **cmd);
void			case_0(t_mini *mini, int *fdf, int i, int j);
void			case_1(t_mini *mini, int *fdf, int i, int j);
void			ft_fork_0(t_mini *mini, int i, int **fd);
void			exec_pip_fat(t_mini *mini);
int				ft_equalexist(char *str);
void			unset_while1(t_mini *mini, t_envs *lista);
void			unset_while2(t_mini *mini, t_envs *lista);
void			exec_fds(int *funciona, int *funciona2);
void			num_pipes_complex(t_mini *mini);
void			free_double_fil(t_mini *mini, int k, char **files);

#endif