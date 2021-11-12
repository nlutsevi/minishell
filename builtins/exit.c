/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlutsevi <nlutsevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:37:22 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/02 23:10:04 by nlutsevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_exit(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int	ft_ismuldig(char **cmd)
{
	int	i;

	if ((!ft_isdigit(cmd[1][0])) && (cmd[1][0] != '-'))
		return (0);
	i = 1;
	while (cmd[1][i])
	{
		if (!ft_isdigit(cmd[1][i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exc3(t_mini *mini, char **cmd, int e)
{
	if (mini->lista_cmds.num_pipes == 1 && e == 1)
	{
		printf("exit\n");
		printf("exit: too many arguments\n");
		mini->error = 1;
	}
	else if (mini->lista_cmds.num_pipes != 1 && e == 1)
	{
		printf("exit: too many arguments\n");
		mini->error = 1;
		free_memory2(mini);
		exit(1);
	}
	else
	{
		printf("exit: %s: numeric argument required\n", cmd[1]);
		mini->error = 255;
		free_memory2(mini);
		exit(255);
	}
}

void	ft_exc2(t_mini *mini, char **cmd, int e)
{
	int	i;

	if (mini->lista_cmds.num_pipes == 1)
		printf("exit\n");
	if (e == 1)
	{
		i = ft_atoi(cmd[1]);
		mini->error = (i % 256);
		free_memory2(mini);
		exit(i % 256);
	}
	else
	{
		printf("exit: %s: numeric argument required\n", cmd[1]);
		mini->error = 255;
		free_memory2(mini);
		exit(255);
	}
}

void	ft_exc1(t_mini *mini)
{
	if (mini->lista_cmds.num_pipes == 1)
		printf("exit\n");
	mini->error = 0;
	free_memory2(mini);
	exit(0);
}
