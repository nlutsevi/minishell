/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlutsevi <nlutsevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 21:19:42 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/02 23:05:00 by nlutsevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*skip_doubleq_aux(char *cmd, int j)
{
	char	temp;
	char	*aux;
	char	*cmd_aux;

	aux = char_to_str('"');
	while (cmd[j] != '\0')
	{
		if (cmd[j + 1] == '\0')
			break ;
		if (cmd[j] == '"')
		{
			temp = cmd[j];
			cmd[j] = cmd[j + 1];
			cmd[j + 1] = temp;
		}
		j++;
	}
	cmd_aux = ft_strtrim(cmd, aux);
	free(cmd);
	free(aux);
	return (cmd_aux);
}

char	**skip_doubleq(char **cmd)
{
	int		i;
	int		j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j] != '\0')
		{
			if (cmd[i][j] == '"')
				cmd[i] = skip_doubleq_aux(cmd[i], j);
			if (cmd[i][j] != '\0')
				j++;
		}
		i++;
	}
	return (cmd);
}

char	*skip_simpleq_aux(char *cmd, int j)
{
	char	temp;
	char	*aux;
	char	*cmd_aux;

	aux = char_to_str('\'');
	while (cmd[j] != '\0')
	{
		if (cmd[j + 1] == '\0')
			break ;
		if (cmd[j] == '\'')
		{
			temp = cmd[j];
			cmd[j] = cmd[j + 1];
			cmd[j + 1] = temp;
		}
		j++;
	}
	cmd_aux = ft_strtrim(cmd, aux);
	free(cmd);
	free(aux);
	return (cmd_aux);
}

char	**skip_simpleq(char **cmd)
{
	int		i;
	int		j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j] != '\0')
		{
			if (cmd[i][j] == '\'')
				cmd[i] = skip_simpleq_aux(cmd[i], j);
			if (cmd[i][j] != '\0')
				j++;
		}
		i++;
	}
	return (cmd);
}
