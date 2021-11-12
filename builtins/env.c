/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperea-d <pperea-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:07:38 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/03 03:24:41 by pperea-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_cmd_env(t_mini *mini)
{
	t_envs	*lista;

	lista = mini->lista_envs;
	while (lista)
	{
		printf("%s\n", lista->name);
		lista = lista->next;
	}
	lista = mini->lista_envs;
	mini->error = 0;
	while (lista)
	{
		if (lista->data == NULL || ft_strncmp(lista->data, "\"\"\0", 3) == 0)
			lista = lista->next;
		else
			lista->data = run_cmd_env_aux(lista->data, lista->name);
		if (lista != NULL)
			lista = lista->next;
	}
	if (mini->lista_cmds.num_pipes != 1)
		exit (0);
}

char	*run_cmd_env_aux(char *data, char *name)
{
	char	*str;
	char	*aux;

	if (data[0] == '"')
		data = ft_strtrim_quotes(data);
	else if (data[0] == '\'')
		data = ft_strtrim_bar(data);
	str = ft_strjoin(name, "=");
	aux = str;
	str = ft_strjoin(aux, data);
	free(aux);
	printf("%s\n", str);
	free(str);
	return (data);
}

char	*ft_strtrim_quotes(char *data)
{
	char	*aux;
	char	*aux_data;

	aux = char_to_str('"');
	aux_data = ft_strtrim(data, aux);
	free(aux);
	free(data);
	return (aux_data);
}

char	*ft_strtrim_bar(char *data)
{
	char	*aux;

	aux = char_to_str('\'');
	data = ft_strtrim(data, aux);
	return (data);
}
