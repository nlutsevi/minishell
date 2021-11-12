/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperea-d <pperea-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:48:34 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/03 04:14:38 by pperea-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*get_simple_files(t_mini *mini, int k, int f)
{
	char	*aux;

	aux = ft_strtrim(mini->lista_cmds.file[k][f], " ");
	free(mini->lista_cmds.file[k][f]);
	mini->lista_cmds.file[k][f] = ft_strdup(aux);
	free(aux);
	return (mini->lista_cmds.file[k][f]);
}

void	get_double_files(t_mini *mini, int k, int f)
{
	int		i;
	char	**files;
	char	**aux_files;

	files = ft_double_files(mini, mini->lista_cmds.file[k][f], k);
	if (mini->double_pipes[k].df == 0)
		mini->lista_cmds.file[k][f] = get_simple_files(mini, k, f);
	else
	{
		free(mini->lista_cmds.file[k][f]);
		mini->lista_cmds.file[k][f] = ft_strdup(files[0]);
		i = 1;
		while (files[i])
		{
			mini->double_pipes[k].pipe = k;
			aux_files = mini->double_pipes[k].doble_pipes;
			mini->double_pipes[k].doble_pipes = \
				ft_words_join(aux_files, files[i]);
			free(aux_files);
			i++;
		}
	}
	free_double_fil(mini, k, files);
}

int	get_quotes_position_dq(t_mini *mini, int j, int k)
{
	mini->double_pipes[k].open_q = j;
	j++;
	if (mini->lista_cmds.str_pipe[k][j] == '\0')
		return (j);
	while (mini->lista_cmds.str_pipe[k][j] != '"')
		j++;
	mini->double_pipes[k].close_q = j;
	return (j);
}

void	get_quotes_position(t_mini *mini, int k)
{
	int		j;

	mini->double_pipes[k].open_q = 0;
	mini->double_pipes[k].close_q = 0;
	j = 0;
	while (mini->lista_cmds.str_pipe[k][j])
	{
		if (mini->lista_cmds.str_pipe[k][j] == '"' && mini->dq)
			j = get_quotes_position_dq(mini, j, k);
		else if (mini->lista_cmds.str_pipe[k][j] == '\'' && mini->sq)
		{
			mini->double_pipes[k].open_q = j;
			j++;
			if (mini->lista_cmds.str_pipe[k][j] == '\0')
				break ;
			while (mini->lista_cmds.str_pipe[k][j] != '\'')
				j++;
			mini->double_pipes[k].close_q = j;
		}
		if (mini->lista_cmds.str_pipe[k][j] != '\0')
			j++;
	}
}

void	get_redirection(t_mini *mini, int k, int num_f)
{
	int		j;
	int		f;

	get_quotes_position(mini, k);
	mini->lista_cmds.file[k] = malloc(sizeof(char *) * (num_f + 1));
	mini->lista_cmds.flag[k] = malloc(sizeof(char *) * (num_f));
	f = 0;
	j = 0;
	while (mini->lista_cmds.str_pipe[k][j])
	{
		if (mini->double_pipes[k].open_q == 0 \
			&& mini->double_pipes[k].close_q == 0)
			get_redirection_noquotes(mini, &j, k, &f);
		else
			get_redirection_quotes(mini, &j, k, &f);
	}
	mini->lista_cmds.file[k][f] = 0;
}
