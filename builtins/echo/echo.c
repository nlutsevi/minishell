/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlutsevi <nlutsevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:33:29 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/02 23:04:34 by nlutsevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_cmd_echo(t_mini *mini, char **cmd)
{
	int		n;
	char	*str;

	str = NULL;
	n = save_n_flag(cmd);
	if (n == 1)
	{
		free(cmd[1]);
		cmd[1] = ft_strdup("");
	}
	if (mini->dq == 1)
		cmd = skip_doubleq(cmd);
	if (mini->sq == 1)
		cmd = skip_simpleq(cmd);
	cmd = set_env_vars(mini, cmd);
	str = join_splitted_cmds(cmd, n);
	if (n == 1)
		write(1, str, ft_strlen(str));
	else
		printf("%s\n", str);
	free(str);
	mini->error = 0;
	if (mini->lista_cmds.num_pipes != 1)
		exit (0);
}

void	check_sq_aux(t_mini *mini, char *cmd, int i)
{
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\'')
			mini->sq = 1;
		i++;
	}
}

void	check_dq_aux(t_mini *mini, char *cmd, int i)
{
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '"')
			mini->dq = 1;
		i++;
	}
}

void	check_sq_dq(char *cmd, t_mini *mini)
{
	int	i;

	i = 0;
	mini->sq = 0;
	mini->dq = 0;
	while (cmd[i] != '\0' && mini->dq == 0)
	{
		if (cmd[i] == '\'')
			check_sq_aux(mini, cmd, i + 1);
		else if (cmd[i] == '"' && mini->sq == 0)
			check_dq_aux(mini, cmd, i + 1);
		i++;
	}
}

int	save_n_flag(char **cmd)
{
	int	n;

	n = 0;
	if (ft_strncmp(cmd[1], "-n", 2) == 0)
		n = 1;
	return (n);
}
