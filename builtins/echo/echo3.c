/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperea-d <pperea-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 21:56:46 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/03 02:11:06 by pperea-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**set_env_vars(t_mini *mini, char **cmd)
{
	int		i;
	int		j;
	char	*aux;

	i = 1;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j] != '\0')
		{
			if (cmd[i][j] == '$' && mini->sq != 1)
			{
				aux = set_value_env_var(cmd[i], mini);
				free(cmd[i]);
				cmd[i] = ft_strdup(aux);
				free(aux);
			}
			if (cmd[i][j] != '\0')
				j++;
		}
		i++;
	}
	return (cmd);
}

char	*set_value_env_var_aux(char *aux, char *cmd_final)
{
	char		*aux_cmd;

	aux_cmd = ft_strjoin(aux, cmd_final);
	free(cmd_final);
	cmd_final = ft_strdup(aux_cmd);
	free(aux_cmd);
	return (cmd_final);
}

char	*set_value_env_var(char *cmd, t_mini *mini)
{
	char		*cmd_final;
	t_envs		*lista;
	char		**aux;

	cmd_final = NULL;
	lista = mini->lista_envs;
	if (cmd[0] == '$')
		cmd = ft_strjoin(" ", cmd);
	aux = ft_split(cmd, '$');
	free(cmd);
	while (lista)
	{
		if (strcmp(aux[1], lista->name) == 0)
			cmd_final = ft_strdup(lista->data);
		lista = lista->next;
	}
	if (cmd_final)
		cmd_final = set_value_env_var_aux(aux[0], cmd_final);
	else
	{
		mini->error = 0;
		cmd_final = ft_strdup("");
	}
	free_str(aux);
	return (cmd_final);
}

char	*join_splitted_cmds_aux(char *str, char *cmd)
{
	char	*aux;

	aux = ft_strjoin(str, cmd);
	free(str);
	str = ft_strjoin(aux, " ");
	free(aux);
	return (str);
}

char	*join_splitted_cmds(char **cmd, int n)
{
	int		i;
	char	*str;
	char	*aux;

	i = 1;
	while (cmd[i])
	{
		if (i == 1 && n == 0)
			str = ft_strjoin(cmd[1], " ");
		else if (i == 1 && n == 1)
			str = ft_strdup(cmd[1]);
		if (i > 1 && cmd[i + 1] != NULL)
			str = join_splitted_cmds_aux(str, cmd[i]);
		else if (i > 1 && cmd[i + 1] == NULL)
		{
			aux = ft_strjoin(str, cmd[i]);
			free(str);
			str = ft_strdup(aux);
			free(aux);
		}
		i++;
	}
	return (str);
}
