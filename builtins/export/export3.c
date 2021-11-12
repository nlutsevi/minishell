/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlutsevi <nlutsevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 19:42:46 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/07/28 18:55:05 by nlutsevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse_export_aux(t_mini *mini, char *str, char **cmd, char **aux)
{
	int	exist;

	run_export_aux(mini, str);
	if (mini->export_equal == 0)
		aux = manage_equal(aux, cmd[0]);
	else if (mini->export_data_null == 1)
		aux = manage_data_null(aux, cmd[0]);
	else
		aux = ft_split(cmd[0], '=');
	exist = parse_existing_export(mini, aux);
	if (exist == 0)
	{
		nodo(&mini->lista_envs, aux);
		free_str(aux);
	}
	env_in_array(mini);
}

char	**parse_export_dq(char **cmd)
{
	char	**aux2;

	aux2 = manage_doubleq(cmd[0]);
	free_str(cmd),
	cmd = aux2;
	free_str(aux2);
	return (cmd);
}

void	parse_export_error(t_mini *mini, char *str)
{
	mini->error = 1;
	printf("bash: export: %s : not a valid identifier\n", str);
	if (mini->lista_cmds.num_pipes != 1)
		exit (1);
}

void	parse_export(t_mini *mini, char *str)
{
	char	**cmd;
	char	**aux;
	char	**aux3;

	aux = NULL;
	cmd = NULL;
	cmd = create_cmd(mini, cmd, str);
	if (cmd[0][0] == '"')
		cmd = parse_export_dq(cmd);
	if (mini->sq == 1)
	{
		aux3 = manage_simpleq(cmd[0]);
		free(cmd);
		cmd = aux3;
	}
	if (!(ft_isalpha(*cmd[0]) && *cmd[0] != '_' && *cmd[0] != '"'))
		parse_export_error(mini, str);
	if (ft_strncmp(cmd[0], "PATH=$PATH:/", 12) == 0)
		parse_expand_path(mini, cmd);
	else
		parse_export_aux(mini, str, cmd, aux);
	free_str(cmd);
}

char	**create_cmd(t_mini *mini, char **cmd, char *str)
{
	cmd = (char **)malloc(sizeof(char *) * 2);
	cmd[0] = ft_strdup(str);
	cmd[1] = NULL;
	check_sq_dq(cmd[0], mini);
	return (cmd);
}
