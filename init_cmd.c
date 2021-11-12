/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlutsevi <nlutsevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:19:40 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/07/29 00:45:17 by nlutsevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	get_cmd(t_mini *mini)
{
	mini->lista_cmds.cmd = ft_strdup(mini->command);
	free(mini->command);
}

void	skip_spaces(t_mini *mini)
{
	int		i;
	int		j;
	char	*aux;

	i = 0;
	j = 0;
	while (i < mini->lista_cmds.num_pipes)
	{
		j = 0;
		if (mini->lista_cmds.str_pipe[i][j] == ' ')
		{
			aux = ft_strdup(mini->lista_cmds.str_pipe[i]);
			free(mini->lista_cmds.str_pipe[i]);
			mini->lista_cmds.str_pipe[i] = ft_strtrim(aux, " ");
			free(aux);
			j++;
		}
		i++;
	}
}

char	*simple_skip_spaces(char *file)
{
	int		i;
	char	*aux;

	i = 0;
	while (file[i] == ' ')
	{
		aux = file;
		file = ft_strtrim(aux, " ");
		free(aux);
		i++;
	}
	i = ft_strlen(file) - 1;
	while (file[i] == ' ')
	{
		aux = file;
		file = ft_strtrim(aux, " ");
		free(aux);
		i--;
	}
	return (file);
}
