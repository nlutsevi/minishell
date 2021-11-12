/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodos_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperea-d <pperea-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 20:03:36 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/03 00:59:56 by pperea-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*char_to_str(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

void	nodos_manager(t_mini *mini)
{
	check_sq_dq(mini->lista_cmds.cmd, mini);
	if (mini->sq == 0 && mini->dq == 0)
	{
		calculate_pipes_s(mini);
		mini->lista_cmds.str_pipe = ft_split(mini->lista_cmds.cmd, '|');
	}
	else
		calculate_pipes_c(mini);
	nodos_manager2(mini);
}

void	mem_alloc_files(t_mini *mini)
{
	int	i;

	mini->lista_cmds.file = malloc(sizeof(char **) \
		* mini->lista_cmds.num_pipes);
	mini->lista_cmds.flag = malloc(sizeof(int *) \
		* mini->lista_cmds.num_pipes);
	mini->double_pipes = malloc(sizeof(t_doble_pipes) \
		* mini->lista_cmds.num_pipes);
	i = 0;
	while (i < mini->lista_cmds.num_pipes)
	{
		mini->double_pipes[i].doble_pipes = NULL;
		mini->double_pipes[i].df = 0;
		i++;
	}
}

void	echo_weird_case(t_mini *mini)
{
	char	**cmds;

	cmds = ft_split(mini->lista_cmds.str_pipe[0], ' ');
	if ((ft_strncmp(cmds[0], "echo", 4) == 0) \
		&& cmds[1] == NULL)
	{
		free(mini->lista_cmds.str_pipe[0]);
		mini->lista_cmds.str_pipe[0] = ft_strdup("echo \n");
	}
	free_str(cmds);
}

void	nodos_manager2(t_mini *mini)
{
	int	i;
	int	num_f;

	mini->lista_cmds.str_pipe[mini->lista_cmds.num_pipes] = NULL;
	free(mini->lista_cmds.cmd);
	mem_alloc_files(mini);
	i = 0;
	while (i < mini->lista_cmds.num_pipes)
	{
		num_f = num_files(mini->lista_cmds.str_pipe[i], mini);
		get_redirection(mini, i, num_f);
		get_pipes(mini, i);
		i++;
	}
	skip_spaces(mini);
	echo_weird_case(mini);
}
