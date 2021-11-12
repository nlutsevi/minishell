/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperea-d <pperea-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 01:06:48 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/03 01:05:07 by pperea-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	get_pipes2(t_mini *mini, int k, int *j)
{
	if (mini->lista_cmds.str_pipe[k][*j] == '>' || \
			mini->lista_cmds.str_pipe[k][*j] == '<')
	{
		while (mini->lista_cmds.str_pipe[k][*j] != '\0')
			mini->lista_cmds.str_pipe[k][*j] = '\0';
	}
	(*j)++;
}

void	get_pipes(t_mini *mini, int k)
{
	int	j;

	j = 0;
	while (mini->lista_cmds.str_pipe[k][j])
	{
		if (mini->double_pipes[k].open_q == 0 && \
			mini->double_pipes[k].close_q == 0)
			get_pipes2(mini, k, &j);
		else
		{
			if ((mini->lista_cmds.str_pipe[k][j] == '>' || \
				mini->lista_cmds.str_pipe[k][j] == '<') && \
				(j < mini->double_pipes[k].open_q || \
				j > mini->double_pipes[k].close_q))
			{
				while (mini->lista_cmds.str_pipe[k][j] != '\0')
					mini->lista_cmds.str_pipe[k][j] = '\0';
			}
			j++;
		}
	}
}
