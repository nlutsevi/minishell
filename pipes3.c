/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlutsevi <nlutsevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 23:14:59 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/02 23:16:11 by nlutsevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_fork_1(t_mini *mini, int i, int **fd)
{
	if (i > 0)
		close(fd[i - 1][READ_END]);
	if (i < mini->lista_cmds.num_pipes - 1)
		close(fd[i][WRITE_END]);
}

void	ft_wait(t_mini *mini, int pid)
{
	int	i;
	int	status;

	i = 0;
	while (i < mini->lista_cmds.num_pipes)
	{
		if (wait(&status) == pid)
		{
			if (WIFEXITED(status))
				mini->error = WEXITSTATUS(status);
		}
		if (status == 11)
		{
			printf("mini_crápula: %s: command not found\n",
				mini->lista_cmds.pipes[0][0]);
			mini->error = 127;
		}
		i++;
	}
}

void	free_fd(t_mini *mini, int **fd)
{
	int	i;

	i = 0;
	while (i < mini->lista_cmds.num_pipes)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

void	exec_pip_child(t_mini *mini)
{
	int		**fd;
	int		pid;
	int		i;

	fd = (int **)malloc(sizeof(int *) * mini->lista_cmds.num_pipes);
	i = 0;
	while (i < mini->lista_cmds.num_pipes)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		if (i < mini->lista_cmds.num_pipes - 1)
			pipe(fd[i]);
		pid = fork();
		if (pid == 0)
			ft_fork_0(mini, i, fd);
		else
			ft_fork_1(mini, i, fd);
		i++;
	}
	signal(SIGINT, new_sig2);
	signal(SIGQUIT, new_sig2);
	ft_wait(mini, pid);
	free_fd(mini, fd);
}

void	execute_pipes(t_mini *mini)
{
	if ((mini->lista_cmds.num_pipes == 1)
		&& (check_builtin(mini->lista_cmds.pipes[0]) == 1))
		exec_pip_fat(mini);
	else
		exec_pip_child(mini);
}
