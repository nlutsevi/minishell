/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlutsevi <nlutsevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:16:25 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/02 23:09:31 by nlutsevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	run_cmd_cd(t_mini *mini, char **cmd)
{
	mini->error = 0;
	if (cmd[1] == NULL)
		builtin_cd_home(mini);
	else if (cmd[1][0] == '/')
		builtin_cd_absolute(mini, cmd);
	else
		builtin_cd_relative(mini, cmd);
	if (mini->lista_cmds.num_pipes != 1)
		exit (0);
	return (1);
}

void	builtin_cd_home(t_mini *mini)
{
	int		i;
	char	cwd[4096];
	char	*aux;

	i = 0;
	getcwd(cwd, 4096);
	update_old_path(mini, cwd);
	while (mini->env_vars[i])
	{
		if (ft_strncmp(mini->env_vars[i], "PWD", 3) == 0)
		{
			aux = builtin_cd_home_aux(mini, mini->env_vars[i]);
			free(mini->env_vars[i]);
			mini->env_vars[i] = ft_strdup(aux);
			free(aux);
		}
		i++;
	}
}

char	*builtin_cd_home_aux2(t_mini *mini, char *pwd, char *str)
{
	t_envs	*lista;

	lista = mini->lista_envs;
	while (lista)
	{
		if (ft_strncmp(pwd, lista->name, 3) == 0)
		{
			free(lista->data);
			lista->data = ft_strdup(str);
			free(str);
			str = ft_strjoin(lista->name, "=");
			pwd = ft_strjoin(str, lista->data);
			free(str);
		}
		lista = lista->next;
	}
	return (pwd);
}

char	*builtin_cd_home_aux(t_mini *mini, char *pwd)
{
	t_envs	*lista;
	char	*str;
	char	*aux;

	lista = mini->lista_envs;
	while (lista)
	{
		if (ft_strncmp("HOME", lista->name, 4) == 0)
			str = ft_strdup(lista->data);
		lista = lista->next;
	}
	if (chdir(str) != 0)
	{
		printf("cd: %s %s", strerror(errno), str);
		mini->error = 1;
		if (mini->lista_cmds.num_pipes != 1)
		{
			free(str);
			exit (1);
		}
	}
	aux = builtin_cd_home_aux2(mini, pwd, str);
	return (aux);
}

void	builtin_cd_absolute(t_mini *mini, char **cmds)
{
	int		i;
	char	cwd[4096];
	char	*aux;

	i = 0;
	getcwd(cwd, 4096);
	update_old_path(mini, cwd);
	if (chdir(cmds[1]) != 0)
	{
		printf("cd: %s %s\n", strerror(errno), cmds[1]);
		mini->error = 1;
		if (mini->lista_cmds.num_pipes != 1)
			exit (1);
	}
	while (mini->env_vars[i])
	{
		if (ft_strncmp(mini->env_vars[i], "PWD", 3) == 0)
		{
			aux = builtin_cd_absolute_aux(mini, cmds, mini->env_vars[i]);
			free(mini->env_vars[i]);
			mini->env_vars[i] = ft_strdup(aux);
			free(aux);
		}
		i++;
	}
}
