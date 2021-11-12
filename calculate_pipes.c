/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperea-d <pperea-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 02:11:46 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/03 02:23:13 by pperea-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	num_files_aux(char *str, int *i, int *c)
{
	(*c)++;
	if (str[*i] == '>' && str[(*i) + 1] == '>')
		(*i)++;
}

void	num_files_aux_dq(char *str, int *i)
{
	(*i)++;
	if (str[*i] == '\0')
		return ;
	while (str[*i] != '\'')
		(*i)++;
}

int	num_files(char *str, t_mini *mini)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && mini->sq)
			num_files_aux_dq(str, &i);
		else if (str[i] == '"' && mini->dq)
		{
			i++;
			if (str[i] == '\0')
				break ;
			while (str[i] != '"')
				i++;
		}
		else if (str[i] == '<' || str[i] == '>')
			num_files_aux(str, &i, &c);
		i++;
	}
	return (c);
}

void	calculate_pipes_s(t_mini *mini)
{
	int	i;

	mini->lista_cmds.num_pipes = 0;
	i = 0;
	while (mini->lista_cmds.cmd[i])
	{
		if (mini->lista_cmds.cmd[i] == '|')
			mini->lista_cmds.num_pipes++;
		i++;
	}
	mini->lista_cmds.num_pipes += 1;
}

void	num_pipes_complex(t_mini *mini)
{
	int	i;

	i = 0;
	mini->lista_cmds.num_pipes = 0;
	while (mini->lista_cmds.cmd[i])
	{
		if ((i < mini->open || i > mini->close) && \
				mini->lista_cmds.cmd[i] == '|')
			mini->lista_cmds.num_pipes++;
		i++;
	}
	mini->lista_cmds.num_pipes += 1;
}
