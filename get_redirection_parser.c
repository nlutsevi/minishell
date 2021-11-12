/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection_parser.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlutsevi <nlutsevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:53:19 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/07/28 22:58:25 by nlutsevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	get_redirection_flag1(t_mini *mini, int k, int j, int f)
{
	char	*tmp;
	char	*aux;

	j++;
	mini->lista_cmds.flag[k][f] = 1;
	while (mini->lista_cmds.str_pipe[k][j] != '>' && \
		mini->lista_cmds.str_pipe[k][j] != '<' && \
		mini->lista_cmds.str_pipe[k][j] != '\0')
	{
		tmp = char_to_str(mini->lista_cmds.str_pipe[k][j]);
		aux = mini->lista_cmds.file[k][f];
		mini->lista_cmds.file[k][f] = ft_strjoin(aux, tmp);
		free(aux);
		free(tmp);
		j++;
	}
	get_double_files(mini, k, f);
	return (j);
}

int	get_redirection_flag0(t_mini *mini, int k, int j, int f)
{
	char	*tmp;
	char	*aux;

	mini->lista_cmds.flag[k][f] = 0;
	while (mini->lista_cmds.str_pipe[k][j] != '>' && \
		mini->lista_cmds.str_pipe[k][j] != '<' &&
		mini->lista_cmds.str_pipe[k][j] != '\0')
	{
		tmp = char_to_str(mini->lista_cmds.str_pipe[k][j]);
		aux = mini->lista_cmds.file[k][f];
		mini->lista_cmds.file[k][f] = ft_strjoin(aux, tmp);
		free(aux);
		free(tmp);
		j++;
	}
	get_double_files(mini, k, f);
	return (j);
}

int	get_redirection_flag2(t_mini *mini, int k, int j, int f)
{
	char	*tmp;
	char	*aux;

	j++;
	mini->lista_cmds.flag[k][f] = 2;
	while (mini->lista_cmds.str_pipe[k][j] != '>' && \
		mini->lista_cmds.str_pipe[k][j] != '<' && \
		mini->lista_cmds.str_pipe[k][j] != '\0')
	{
		tmp = char_to_str(mini->lista_cmds.str_pipe[k][j]);
		aux = mini->lista_cmds.file[k][f];
		mini->lista_cmds.file[k][f] = ft_strjoin(aux, tmp);
		free(aux);
		free(tmp);
		j++;
	}
	get_double_files(mini, k, f);
	return (j);
}

int	get_redirection_flagminus1(t_mini *mini, int k, int j, int f)
{
	char	*tmp;
	char	*aux;

	mini->lista_cmds.flag[k][f] = -1;
	while (mini->lista_cmds.str_pipe[k][j] != '>' && \
		mini->lista_cmds.str_pipe[k][j] != '<' && \
		mini->lista_cmds.str_pipe[k][j] != '\0')
	{
		tmp = char_to_str(mini->lista_cmds.str_pipe[k][j]);
		aux = mini->lista_cmds.file[k][f];
		mini->lista_cmds.file[k][f] = ft_strjoin(aux, tmp);
		free(aux);
		free(tmp);
		j++;
	}
	get_double_files(mini, k, f);
	return (j);
}
