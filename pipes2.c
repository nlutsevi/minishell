/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperea-d <pperea-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 23:13:36 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/03 01:00:37 by pperea-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	case_2(t_mini *mini, int *fdf, int i, int j)
{
	*fdf = open(mini->lista_cmds.file[i][j], O_RDONLY);
	dup2(*fdf, STDIN_FILENO);
}

void	case_3(t_mini *mini, int *fdf, int i, int j)
{
	char	*line;

	line = ft_strdup("");
	*fdf = open(".tmp", O_WRONLY | O_TRUNC | O_CREAT, 0700);
	while (ft_strcmp (line, mini->lista_cmds.file[i][j]) != 0)
	{
		write(1, "> ", 2);
		get_next_line(1, &line);
		if (strcmp (line, mini->lista_cmds.file[i][j]) != 0)
		{
			write(*fdf, line, ft_strlen(line));
			write(*fdf, "\n", 1);
		}
	}
	free(line);
	close(*fdf);
	*fdf = open(".tmp", O_RDONLY);
	dup2(*fdf, STDIN_FILENO);
}

void	exec_pip_fat(t_mini *mini)
{
	int		funciona;
	int		funciona2;
	int		j;
	int		fdf;

	j = 0;
	funciona = dup(STDOUT_FILENO);
	funciona2 = dup(STDIN_FILENO);
	while (mini->lista_cmds.file[0][j])
	{
		if (mini->lista_cmds.flag[0][j] == 0)
			case_0(mini, &fdf, 0, j);
		else if (mini->lista_cmds.flag[0][j] == 1)
			case_1(mini, &fdf, 0, j);
		else if (mini->lista_cmds.flag[0][j] == -1)
			case_2(mini, &fdf, 0, j);
		else
			case_3(mini, &fdf, 0, j);
		close(fdf);
		unlink(".tmp");
		j++;
	}
	check_cmd(mini, mini->lista_cmds.pipes[0]);
	exec_fds(&funciona, &funciona2);
}

void	ft_fork_01(t_mini *mini, int i, int **fd)
{
	if (i < mini->lista_cmds.num_pipes - 1)
		close(fd[i][READ_END]);
	if (i > 0)
	{
		dup2(fd[i - 1][READ_END], STDIN_FILENO);
		close(fd[i - 1][READ_END]);
	}
	if (i < mini->lista_cmds.num_pipes - 1)
	{
		dup2(fd[i][WRITE_END], STDOUT_FILENO);
		close(fd[i][WRITE_END]);
	}
}

void	ft_fork_0(t_mini *mini, int i, int **fd)
{
	int		fdf;
	int		j;

	ft_fork_01(mini, i, fd);
	j = 0;
	while (mini->lista_cmds.file[i][j])
	{
		if (mini->lista_cmds.flag[i][j] == 0)
			case_0(mini, &fdf, i, j);
		else if (mini->lista_cmds.flag[i][j] == 1)
			case_1(mini, &fdf, i, j);
		else if (mini->lista_cmds.flag[i][j] == -1)
			case_2(mini, &fdf, i, j);
		else
			case_3(mini, &fdf, i, j);
		close(fdf);
		unlink(".tmp");
		j++;
	}
	signal(SIGQUIT, new_sig2);
	check_cmd(mini, mini->lista_cmds.pipes[i]);
}
