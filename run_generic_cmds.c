/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_generic_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlutsevi <nlutsevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:58:04 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/02 23:26:26 by nlutsevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	run_generic_absolute(t_mini *mini, char *cmd)
{
	char	**cmds;
	char	cwd[4096];

	cmds = (char **)malloc(sizeof(char *) * 2);
	getcwd(cwd, 4096);
	cmds[0] = ft_strjoin(cwd, cmd);
	cmds[1] = NULL;
	mini->ret = execve(cmds[0], cmds, mini->env_vars);
}

int	run_generic_cmd_aux(t_mini *mini, char **path, char **cmd, int count)
{
	int		k;

	k = ft_strlen(path[count]);
	path[count] = ft_strjoin(path[count], "/");
	path[count] = ft_strjoin(path[count], cmd[0]);
	mini->ret = execve(path[count], cmd, mini->env_vars);
	return (k);
}

int	run_generic_generic(t_mini *mini, char **path, char **cmd, int *count)
{
	int	k;

	k = run_generic_cmd_aux(mini, path, cmd, *count);
	(*count)++;
	return (k);
}

void	run_generic_cmd(t_mini *mini, char **cmd)
{
	char	**path;
	int		k;
	int		count;
	int		r;
	size_t	i;

	i = 0;
	count = 0;
	r = flag_absolute(cmd[0]);
	if (!mini->pathname)
	{
		printf("mini_crápula: %s: command not found\n", cmd[0]);
		exit (127);
	}
	path = ft_split(mini->pathname, ':');
	while (i < ft_strlen(mini->pathname))
	{
		if (cmd[0][0] == '/')
			mini->ret = execve(cmd[0], cmd, mini->env_vars);
		else if (r == 1)
			run_generic_absolute(mini, cmd[0]);
		else
			k = run_generic_generic(mini, path, cmd, &count);
		i += k;
	}
}
