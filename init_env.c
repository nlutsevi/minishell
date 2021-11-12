/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperea-d <pperea-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:18:27 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/03 01:06:52 by pperea-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	save_env_vars(char *env[], t_mini *mini)
{
	int		i;
	char	**vars;

	i = 0;
	while (env[i])
	{
		vars = ft_split(env[i], '=');
		nodo(&mini->lista_envs, vars);
		free_str(vars);
		i++;
	}
	searchpath(mini);
}

int	length_env(t_mini *mini)
{
	int		i;
	t_envs	*lista;

	i = 0;
	lista = mini->lista_envs;
	while (lista)
	{
		i++;
		lista = lista->next;
	}
	return (i);
}

void	env_in_array_aux(t_mini *mini, int *i, char *name, char *data)
{
	char	*aux;

	mini->env_vars[*i] = ft_strjoin(name, "=");
	aux = ft_strdup(mini->env_vars[*i]);
	free(mini->env_vars[*i]);
	mini->env_vars[*i] = ft_strjoin(aux, data);
	free(aux);
	(*i)++;
}

void	env_in_array(t_mini *mini)
{
	t_envs	*lista;
	int		i;

	if (mini->env_vars)
		free_str((mini->env_vars));
	i = length_env(mini);
	mini->env_vars = (char **)malloc(sizeof(char *) * (i + 1));
	lista = mini->lista_envs;
	i = 0;
	while (lista)
	{
		if (lista->data != NULL)
			env_in_array_aux(mini, &i, lista->name, lista->data);
		else
		{
			mini->env_vars[i] = ft_strdup(lista->name);
			i++;
		}
		lista = lista->next;
	}
	mini->env_vars[i] = NULL;
}
