/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlutsevi <nlutsevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 00:48:30 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/07/28 18:36:59 by nlutsevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*update_old_path_aux(char **name, char **data, char *cwd)
{
	char	*str;
	char	*var;

	str = ft_strjoin(*name, "=");
	var = ft_strjoin(str, cwd);
	free(str);
	free(*data);
	*data = ft_strdup(cwd);
	return (var);
}

void	update_old_path(t_mini *mini, char *cwd)
{
	int		i;
	t_envs	*lista;

	i = 0;
	lista = mini->lista_envs;
	while (mini->env_vars[i])
	{
		if (ft_strncmp(mini->env_vars[i], "OLDPWD", 6) == 0)
		{
			while (lista)
			{
				if (ft_strncmp(mini->env_vars[i], lista->name, 6) == 0)
				{
					free(mini->env_vars[i]);
					mini->env_vars[i] = update_old_path_aux(&lista->name, \
						&lista->data, cwd);
				}
				lista = lista->next;
			}
		}
		i++;
	}
}

char	*builtin_cd_absolute_aux(t_mini *mini, char **cmds, char *pwd)
{
	t_envs	*lista;
	char	*str;

	lista = mini->lista_envs;
	while (lista)
	{
		if (ft_strncmp(pwd, lista->name, 3) == 0)
		{
			free(lista->data);
			lista->data = ft_strdup(cmds[1]);
			str = ft_strjoin(lista->name, "=");
			pwd = ft_strjoin(str, lista->data);
			free(str);
		}
		lista = lista->next;
	}
	return (pwd);
}

void	builtin_cd_relative(t_mini *mini, char **cmds)
{
	int		i;
	char	cwd[4096];
	char	*aux;

	i = 0;
	getcwd(cwd, 4096);
	update_old_path(mini, cwd);
	if (chdir(cmds[1]) != 0)
	{
		printf("cd: %s: %s\n", cmds[1], strerror(errno));
		mini->error = 1;
		if (mini->lista_cmds.num_pipes != 1)
			exit (1);
	}
	while (mini->env_vars[i])
	{
		if (ft_strncmp(mini->env_vars[i], "PWD", 3) == 0)
		{
			aux = builtin_cd_relative_aux(mini, mini->env_vars[i]);
			free(mini->env_vars[i]);
			mini->env_vars[i] = ft_strdup(aux);
			free(aux);
		}
		i++;
	}
}

char	*builtin_cd_relative_aux(t_mini *mini, char *pwd)
{
	t_envs	*lista;
	char	*str;
	char	cwd[4096];

	lista = mini->lista_envs;
	getcwd(cwd, 4096);
	while (lista)
	{
		if (ft_strncmp(pwd, lista->name, 3) == 0)
		{
			free(lista->data);
			lista->data = ft_strdup(cwd);
			str = ft_strjoin(lista->name, "=");
			pwd = ft_strjoin(str, lista->data);
			free(str);
		}
		lista = lista->next;
	}
	return (pwd);
}
