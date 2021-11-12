/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlutsevi <nlutsevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 15:37:07 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/07/28 19:24:37 by nlutsevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_str(char **str)
{
	int		i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	free_int(t_mini *mini, int **flag)
{
	int		i;

	i = 0;
	while (i < mini->lista_cmds.num_pipes)
	{
		free(flag[i]);
		i++;
	}
	free(flag);
}

void	free_matrix(t_mini *mini, char ***str)
{
	int		i;

	i = 0;
	while (i < mini->lista_cmds.num_pipes)
	{
		free_str(str[i]);
		i++;
	}
	free(str);
}

void	free_tritrix(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < mini->lista_cmds.num_pipes)
	{
		if (mini->double_pipes[i].doble_pipes != NULL)
		{
			free_str(mini->double_pipes[i].doble_pipes);
		}
		i++;
	}
	free(mini->double_pipes);
}

void	free_str2(t_mini *mini)
{
	int		i;

	i = 0;
	while (mini->env_vars[i] != NULL)
	{
		free(mini->env_vars[i]);
		i++;
	}
	free(mini->env_vars);
}
