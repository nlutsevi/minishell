/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperea-d <pperea-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 00:11:42 by pperea-d          #+#    #+#             */
/*   Updated: 2021/08/03 03:49:23 by pperea-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_equalexist(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	unset_while1(t_mini *mini, t_envs *lista)
{
	t_envs	*aux;

	aux = lista->next->next;
	free(lista->next->name);
	free(lista->next->data);
	free(lista->next);
	lista->next = aux;
	env_in_array(mini);
}

void	unset_while2(t_mini *mini, t_envs *lista)
{
	t_envs	*aux;

	aux = lista->next;
	free(lista->name);
	free(lista->data);
	free(lista);
	mini->lista_envs = aux;
	env_in_array(mini);
}
