/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_pipes2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperea-d <pperea-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 02:22:53 by pperea-d          #+#    #+#             */
/*   Updated: 2021/08/03 04:20:31 by pperea-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	calculate_pipes_c2(t_mini *mini, int *p, int i)
{
	if ((mini->lista_cmds.cmd[i] == '|' || \
			mini->lista_cmds.cmd[i + 1] == '\0') && i < mini->open)
		*p = calculate_pipes_c_before(mini, i, *p);
	else if ((mini->lista_cmds.cmd[i] == '|' || \
			mini->lista_cmds.cmd[i + 1] == '\0') && i > mini->open)
		*p = calculate_pipes_c_after(mini, i, *p);
}

void	calculate_pipes_c(t_mini *mini)
{
	int	i;
	int	p;

	position_comillas(mini);
	num_pipes_complex(mini);
	mini->lista_cmds.str_pipe = (char **)malloc(sizeof(char *) * \
		(mini->lista_cmds.num_pipes + 1));
	i = 0;
	p = 0;
	if (mini->lista_cmds.num_pipes == 1)
		mini->lista_cmds.str_pipe[0] = ft_strdup(mini->lista_cmds.cmd);
	else
	{
		while (mini->lista_cmds.cmd[i])
		{
			if (p < mini->lista_cmds.num_pipes)
				calculate_pipes_c2(mini, &p, i);
			i++;
		}
	}
}
