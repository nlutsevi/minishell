/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlutsevi <nlutsevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:19:40 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/02 22:07:22 by nlutsevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	check_builtin(char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "$", 1) == 0)
		return (1);
	else
		return (0);
}

void	check_cmd(t_mini *mini, char **cmd)
{
	char	*str;

	if (ft_strncmp(cmd[0], "echo", 4) == 0)
		run_cmd_echo(mini, cmd);
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		run_cmd_pwd(mini);
	else if (ft_strncmp(cmd[0], "cd", 2) == 0)
		run_cmd_cd(mini, cmd);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
		ft_exit(mini, cmd);
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
		run_cmd_env(mini);
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
		run_export(mini, cmd[1]);
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
		run_unset(mini, cmd[1]);
	else if (ft_strncmp(cmd[0], "$", 1) == 0)
	{
		str = set_value_env_var(cmd[0], mini);
		printf("%s\n", str);
	}
	else if (ft_strncmp(cmd[0], "./", 2) == 0)
		run_minishell(cmd[0], mini);
	else
		run_generic_cmd(mini, cmd);
}

void	run_minishell(char *cmd, t_mini *mini)
{
	char	**cmds;
	char	cwd[4096];
	char	*str;
	char	*aux;

	cmds = (char **)malloc(sizeof(char *) * 2);
	cmds = ft_split(cmd, '/');
	aux = ft_strjoin("/", cmds[1]);
	free(cmds[0]);
	free(cmds[1]);
	cmds[0] = ft_strdup(aux);
	free(aux);
	cmds[1] = NULL;
	getcwd(cwd, 4096);
	str = ft_strjoin(cwd, cmds[0]);
	free(cmds[0]);
	cmds[0] = ft_strdup(str);
	free(str);
	run_generic_cmd(mini, cmds);
}

int	flag_absolute(char *cmd)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			r = 1;
		i++;
	}
	return (r);
}
