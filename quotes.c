/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlutsevi <nlutsevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 01:33:22 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/07/29 01:45:24 by nlutsevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	position_sq(t_mini *mini, int *i)
{
	if (mini->lista_cmds.cmd[*i] == '\'')
	{
		mini->open = *i;
		(*i) += 1;
		while (mini->lista_cmds.cmd[*i])
		{
			if (mini->lista_cmds.cmd[*i] == '\'')
				mini->close = *i;
			(*i)++;
		}
	}
	if (mini->lista_cmds.cmd[*i] != '\0')
		(*i)++;
}

void	position_dq(t_mini *mini, int *i)
{
	if (mini->lista_cmds.cmd[*i] == '"')
	{
		mini->open = *i;
		(*i) += 1;
		while (mini->lista_cmds.cmd[*i])
		{
			if (mini->lista_cmds.cmd[*i] == '"')
				mini->close = *i;
			(*i)++;
		}
	}
	if (mini->lista_cmds.cmd[*i] != '\0')
		(*i)++;
}

void	position_comillas(t_mini *mini)
{
	int	i;

	mini->open = 0;
	mini->close = 0;
	if (mini->sq)
	{
		i = 0;
		while (mini->lista_cmds.cmd[i])
			position_sq(mini, &i);
	}
	else if (mini->dq)
	{
		i = 0;
		while (mini->lista_cmds.cmd[i])
			position_dq(mini, &i);
	}
}
