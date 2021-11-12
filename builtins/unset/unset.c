/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperea-d <pperea-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 20:29:34 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/03 00:13:51 by pperea-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isnumber(char *str)
{
	int	i;

	if ((!ft_isdigit(*str)) && (*str != '-'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	unset_while(t_mini *mini, char *str)
{
	t_envs	*lista;

	lista = mini->lista_envs;
	while (lista)
	{
		if (str == NULL)
			break ;
		if (ft_strncmp(lista->name, str, ft_strlen(lista->name)) == 0)
		{
			unset_while2(mini, lista);
			break ;
		}
		if (lista->next)
		{
			if (ft_strncmp(lista->next->name, str, \
				ft_strlen(lista->next->name)) == 0)
			{
				unset_while1(mini, lista);
				break ;
			}
		}
		lista = lista->next;
	}
}

void	run_unset(t_mini *mini, char *str)
{
	mini->error = 0;
	unset_while(mini, str);
	if (ft_strncmp(str, "PATH", 4) == 0 && str != NULL)
	{
		free(mini->pathname);
		mini->pathname = NULL;
		env_in_array(mini);
	}
	if (str && (*str == '-'))
	{
		mini->error = 2;
		printf("unset: %s : invalid option\n", str);
		if (mini->lista_cmds.num_pipes != 1)
			exit (2);
	}
	else if (str && (ft_isnumber(str) || ft_equalexist(str)))
	{
		mini->error = 1;
		printf("unset: %s: not a valid identifier\n", str);
		if (mini->lista_cmds.num_pipes != 1)
			exit (1);
	}
	if (mini->lista_cmds.num_pipes != 1)
		exit (0);
}
