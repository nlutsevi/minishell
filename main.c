/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperea-d <pperea-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 18:25:56 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/03 02:31:58 by pperea-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_global = 0;

void	new_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_global = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signals(void)
{
	signal(SIGINT, new_sig);
	signal(SIGQUIT, SIG_IGN);
}

void	new_sig2(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
	}
	if (sig == SIGQUIT)
		printf("Quit: 3\n");
}

void	init_mini_vars(t_mini *mini)
{
	t_envs		*lista;

	mini->ret = 0;
	mini->error = 0;
	mini->env_vars = NULL;
	lista = NULL;
	mini->lista_envs = lista;
}

int	main(int argc, char *argv[], char *env[])
{
	t_mini		mini;

	(void)argv;
	init_mini_vars(&mini);
	if (argc == 1)
	{
		save_env_vars(env, &mini);
		env_in_array(&mini);
		while (1)
		{
			signals();
			prompt_msg(&mini);
			if (g_global == 1)
			{
				mini.error = 1;
				g_global = 0;
			}
			nodos_manager(&mini);
			init_pipes_cmd(&mini);
			execute_pipes(&mini);
			free_memory2(&mini);
		}
	}
	return (mini.ret);
}
