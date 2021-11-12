/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlutsevi <nlutsevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:05:15 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/02 23:05:45 by nlutsevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_cmd_existing_pwd_aux(t_mini *mini, int i)
{
	char	*str;
	char	*aux;
	t_envs	*lista;

	lista = mini->lista_envs;
	while (lista)
	{
		if (ft_strncmp(lista->name, "PWD", 3) == 0)
		{
			printf("%s\n", lista->data);
			str = ft_strjoin(lista->name, "=");
			aux = ft_strjoin(str, lista->data);
			free(mini->env_vars[i]),
			mini->env_vars[i] = aux;
			free(str);
		}
		lista = lista->next;
	}
}

void	run_cmd_existing_pwd(t_mini *mini)
{
	int		i;

	i = 0;
	while (mini->env_vars[i] != NULL)
	{
		if (ft_strncmp(mini->env_vars[i], "PWD", 3) == 0)
			run_cmd_existing_pwd_aux(mini, i);
		i++;
	}
}

int	run_cmd_pwd(t_mini *mini)
{
	t_envs	*lista;
	char	cwd[4096];
	int		exist;

	exist = 0;
	mini->error = 0;
	getcwd(cwd, 4096);
	lista = mini->lista_envs;
	while (lista)
	{
		if (ft_strncmp(lista->name, "PWD", 3) == 0)
			exist = 1;
		lista = lista->next;
	}
	if (exist)
		run_cmd_existing_pwd(mini);
	else
	{
		printf("%s\n", cwd);
	}
	if (mini->lista_cmds.num_pipes != 1)
		exit (0);
	return (1);
}
