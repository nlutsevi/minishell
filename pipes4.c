/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperea-d <pperea-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 23:15:53 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/03 01:00:43 by pperea-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	print_pipes(t_mini *mini)
{
	int		i;
	int		j;

	i = 0;
	while (i < mini->lista_cmds.num_pipes)
	{
		j = 0;
		while (mini->lista_cmds.pipes[i][j])
		{
			printf("cmd[%d][%d]: %s\n", i, j, mini->lista_cmds.pipes[i][j]);
			printf("cmd[%d][%d]: %p\n", i, j, mini->lista_cmds.pipes[i][j]);
			j++;
		}
		j = 0;
		while (mini->lista_cmds.file[i][j])
		{
			printf("file[%d][%d]: %s\n", i, j, mini->lista_cmds.file[i][j]);
			printf("file[%d][%d]: %p\n", i, j, mini->lista_cmds.file[i][j]);
			printf("flag[%d][%d]: %d\n", i, j, mini->lista_cmds.flag[i][j]);
			printf("flag[%d][%d]: %p\n", i, j, &mini->lista_cmds.flag[i][j]);
			j++;
		}
		i++;
	}
}

void	exec_fds(int *funciona, int *funciona2)
{
	dup2(*funciona, STDOUT_FILENO);
	dup2(*funciona2, STDIN_FILENO);
	close(*funciona);
	close(*funciona2);
}
