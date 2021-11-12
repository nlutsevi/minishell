/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodos_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperea-d <pperea-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 19:24:28 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/03 01:18:53 by pperea-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_envs	*new_nodo(char **vars)
{
	t_envs	*envs;

	envs = malloc(sizeof(t_envs));
	if (!(envs))
		printf("Error al reservar memoria para nodo\n");
	envs->name = ft_strdup(vars[0]);
	envs->data = ft_strdup(vars[1]);
	return (envs);
}

void	add_nodo(t_envs *nodo, t_envs **lista)
{
	t_envs	*last;

	nodo->next = NULL;
	if (*lista == NULL)
		*lista = nodo;
	else
	{
		last = *lista;
		while (last->next != NULL)
			last = last->next;
		last->next = nodo;
	}
}

void	nodo(t_envs **lista, char **vars)
{
	t_envs		*nodo;

	nodo = new_nodo(vars);
	add_nodo(nodo, lista);
}

void	delete_lista(t_envs **lista)
{
	t_envs	*p;
	t_envs	*q;

	p = *lista;
	while (p != NULL)
	{
		q = p->next;
		free(p->name);
		free(p->data);
		free(p);
		p = q;
	}
	*lista = NULL;
}
