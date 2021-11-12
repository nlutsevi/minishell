/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperea-d <pperea-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:24:00 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/03 03:32:38 by pperea-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_memory(t_mini *mini)
{
	free_matrix(mini, mini->lista_cmds.pipes);
	free_tritrix(mini);
	free_matrix(mini, mini->lista_cmds.file);
	free_int(mini, mini->lista_cmds.flag);
	delete_lista(&mini->lista_envs);
}

void	free_memory2(t_mini *mini)
{
	free_matrix(mini, mini->lista_cmds.pipes);
	free_tritrix(mini);
	free_matrix(mini, mini->lista_cmds.file);
	free_int(mini, mini->lista_cmds.flag);
}
