/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_complex_pipes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperea-d <pperea-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 02:20:17 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/03 03:20:22 by pperea-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	calculate_pipes_c_before(t_mini *mini, int i, int p)
{
	int	f;
	int	n;

	f = 0;
	if (p == 0)
	{
		mini->lista_cmds.str_pipe[p] = (char *)malloc(sizeof(char) * (i + 1));
		ft_strlcpy(mini->lista_cmds.str_pipe[p], mini->lista_cmds.cmd, (i + 1));
		p++;
	}
	else
	{
		f = i;
		n = 0;
		i = 0;
		while (n < p)
		{
			i += ft_strlen(mini->lista_cmds.str_pipe[n]) + 1;
			n++;
		}
		mini->lista_cmds.str_pipe[p] = \
			ft_substr(mini->lista_cmds.cmd, i, (f - i));
		p++;
	}
	return (p);
}

int	length_complex_pipe(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->lista_cmds.cmd[i])
	{
		if (mini->lista_cmds.cmd[i] == '\'' && mini->sq)
		{
			i++;
			while (mini->lista_cmds.cmd[i] != '\'')
				i++;
		}
		else if (mini->lista_cmds.cmd[i] == '"' && mini->dq)
		{
			i++;
			while (mini->lista_cmds.cmd[i] != '"')
				i++;
		}
		else if (mini->lista_cmds.cmd[i] == '|')
			break ;
		i++;
	}
	return (i);
}

int	length_pipe(t_mini *mini, int i)
{
	while (mini->lista_cmds.cmd[i])
	{
		if (mini->lista_cmds.cmd[i] == '\'' && mini->sq)
		{
			i++;
			while (mini->lista_cmds.cmd[i] != '\'')
				i++;
		}
		else if (mini->lista_cmds.cmd[i] == '"' && mini->dq)
		{
			i++;
			while (mini->lista_cmds.cmd[i] != '"')
				i++;
		}
		else if (mini->lista_cmds.cmd[i] == '|')
			break ;
		if (mini->lista_cmds.cmd[i] != '\0')
			i++;
	}
	return (i);
}

int	length_subpipe(t_mini *mini, int p)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (n < p)
	{
		i += ft_strlen(mini->lista_cmds.str_pipe[n]) + 1;
		n++;
	}
	return (i);
}

int	calculate_pipes_c_after(t_mini *mini, int i, int p)
{
	int	f;

	f = 0;
	if (p == 0)
	{
		i = length_complex_pipe(mini);
		mini->lista_cmds.str_pipe[p] = (char *)malloc(sizeof(char) * (i + 1));
		ft_strlcpy(mini->lista_cmds.str_pipe[p], mini->lista_cmds.cmd, (i + 1));
		p++;
	}
	else
	{
		i = length_subpipe(mini, p);
		f = i + 1;
		i = length_pipe(mini, i);
		mini->lista_cmds.str_pipe[p] = \
			ft_substr(mini->lista_cmds.cmd, f, (i - f));
		p++;
	}
	return (p);
}
