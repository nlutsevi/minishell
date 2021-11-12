/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlutsevi <nlutsevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 19:28:00 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/02 23:14:19 by nlutsevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	function_dollar(t_mini *mini, int i, int j)
{
	char	*aux;

	if (ft_strncmp(mini->lista_cmds.pipes[i][j], "$?", 2) == 0)
	{
		aux = ft_itoa(mini->error);
		free(mini->lista_cmds.pipes[i][j]);
		mini->lista_cmds.pipes[i][j] = ft_strdup(aux);
		free(aux);
	}
}

void	init_pipes_cmd(t_mini *mini)
{
	int		i;
	int		j;

	mini->lista_cmds.pipes = NULL;
	mini->lista_cmds.pipes = (char ***)malloc(sizeof(char **)
			* mini->lista_cmds.num_pipes);
	i = 0;
	while (i < mini->lista_cmds.num_pipes)
	{
		mini->lista_cmds.pipes[i] = ft_split(mini->lista_cmds.str_pipe[i], ' ');
		if (mini->double_pipes[i].df == 1)
			add_double_files(mini, i);
		j = 0;
		while (mini->lista_cmds.pipes[i][j])
		{
			function_dollar(mini, i, j);
			j++;
		}
		i++;
	}
	free_str(mini->lista_cmds.str_pipe);
}

void	add_double_files(t_mini *mini, int i)
{
	int		j;
	char	**aux;

	j = 0;
	while (mini->double_pipes[i].doble_pipes[j])
	{
		aux = mini->lista_cmds.pipes[i];
		mini->lista_cmds.pipes[i]
			= ft_words_join(aux, mini->double_pipes[i].doble_pipes[j]);
		free(aux);
		j++;
	}
}

void	case_0(t_mini *mini, int *fdf, int i, int j)
{
	*fdf = open(mini->lista_cmds.file[i][j], O_WRONLY
			| O_TRUNC | O_CREAT, 0700);
	dup2(*fdf, STDOUT_FILENO);
}

void	case_1(t_mini *mini, int *fdf, int i, int j)
{
	*fdf = open(mini->lista_cmds.file[i][j], O_WRONLY
			| O_APPEND | O_CREAT, 0700);
	dup2(*fdf, STDOUT_FILENO);
}
