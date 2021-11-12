/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperea-d <pperea-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 22:59:04 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/03 04:14:42 by pperea-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	get_redirection_aux1(t_mini *mini, int j, int k, int f)
{
	mini->lista_cmds.file[k][f] = ft_strdup("");
	j++;
	if (mini->lista_cmds.str_pipe[k][j] == '>')
		j = get_redirection_flag1(mini, k, j, f);
	else
		j = get_redirection_flag0(mini, k, j, f);
	return (j);
}

int	get_redirection_aux2(t_mini *mini, int j, int k, int f)
{
	mini->lista_cmds.file[k][f] = ft_strdup("");
	j++;
	if (mini->lista_cmds.str_pipe[k][j] == '<')
		j = get_redirection_flag2(mini, k, j, f);
	else
		j = get_redirection_flagminus1(mini, k, j, f);
	return (j);
}

void	get_redirection_noquotes(t_mini *mini, int *j, int k, int *f)
{
	if (mini->lista_cmds.str_pipe[k][*j] == '>')
	{
		*j = get_redirection_aux1(mini, *j, k, *f);
		(*f)++;
	}
	else if (mini->lista_cmds.str_pipe[k][*j] == '<')
	{
		*j = get_redirection_aux2(mini, *j, k, *f);
		(*f)++;
	}
	else
		(*j)++;
}

void	get_redirection_quotes(t_mini *mini, int *j, int k, int *f)
{
	if (mini->lista_cmds.str_pipe[k][*j] == '>' && \
		(*j < mini->double_pipes[k].open_q || \
		*j > mini->double_pipes[k].close_q))
	{
		*j = get_redirection_aux1(mini, *j, k, *f);
		(*f)++;
	}
	else if (mini->lista_cmds.str_pipe[k][*j] == '<' && \
		(*j < mini->double_pipes[k].open_q || \
		*j > mini->double_pipes[k].close_q))
	{
		mini->lista_cmds.file[k][*f] = ft_strdup("");
		(*j)++;
		if (mini->lista_cmds.str_pipe[k][*j] == '<')
			*j = get_redirection_flag2(mini, k, *j, *f);
		else
			*j = get_redirection_flagminus1(mini, k, *j, *f);
		(*f)++;
	}
	else
		(*j)++;
}

void	free_double_fil(t_mini *mini, int k, char **files)
{
	if (mini->double_pipes[k].df == 0)
		free(files);
	else if (mini->double_pipes[k].df == 1)
		free_str(files);
}
