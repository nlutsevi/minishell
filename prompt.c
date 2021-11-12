/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlutsevi <nlutsevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 00:53:21 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/02 23:02:43 by nlutsevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	searchpath(t_mini *mini)
{
	t_envs	*lista;

	lista = mini->lista_envs;
	while (lista)
	{
		if (ft_strncmp(lista->name, "PATH", 4) == 0)
			mini->pathname = ft_strdup(lista->data);
		lista = lista->next;
	}
}

int	ft_line_spaces(char *cmd)
{
	int	i;
	int	l;
	int	len;
	int	spaces;

	i = 0;
	l = 0;
	spaces = 0;
	len = ft_strlen(cmd);
	while (cmd[i] != '\0')
	{
		if (cmd[i] == ' ')
			l++;
		i++;
	}
	if (len == l)
		spaces = 1;
	return (spaces);
}

void	prompt_msg(t_mini *mini)
{
	char	*line;
	int		spaces;

	line = readline(CYAN"mini_crápula ☠👻💀🦇🌙 ▸  "WHITE);
	if (line == NULL)
		ft_exit2 (mini);
	add_history(line);
	spaces = ft_line_spaces(line);
	mini->lista_cmds.cmd = ft_strdup(line);
	free(line);
	if (ft_strncmp(mini->lista_cmds.cmd, "\0", 1) == 0 || spaces)
	{
		free(mini->lista_cmds.cmd);
		prompt_msg(mini);
	}
}
