/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperea-d <pperea-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 20:29:01 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/03 03:29:54 by pperea-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_export(t_mini *mini, char *str)
{
	mini->error = 0;
	if (str == NULL)
		print_ordered_env(mini);
	else
		parse_export(mini, str);
	if (mini->lista_cmds.num_pipes != 1)
		exit (0);
}

void	print_ordered_env(t_mini *mini)
{
	char	**vars;
	int		i;
	int		env_len;

	vars = mini->env_vars;
	env_len = 0;
	while (vars[env_len])
		env_len++;
	mini->vars_ordered = 0;
	vars_loop(mini, vars, env_len);
	i = 0;
	while (vars[i])
	{
		printf("declare -x %s\n", vars[i]);
		i++;
	}
}

void	vars_loop(t_mini *mini, char **vars, int env_len)
{
	int		i;
	char	*temp;

	while (vars && mini->vars_ordered == 0)
	{
		mini->vars_ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (strcmp(vars[i], vars[i + 1]) > 0)
			{
				temp = vars[i];
				vars[i] = vars[i + 1];
				vars[i + 1] = temp;
				mini->vars_ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}

void	parse_expand_path(t_mini *mini, char **cmd)
{
	t_envs	*lista;
	char	**aux;
	char	*str_aux;
	char	*str;

	lista = mini->lista_envs;
	while (lista)
	{
		if (ft_strncmp(lista->name, "PATH", 4) == 0)
		{
			aux = ft_split(cmd[0], ':');
			str_aux = ft_strjoin(lista->data, ":\0");
			free(lista->data);
			str = ft_strjoin(str_aux, aux[1]);
			free_str(aux);
			free(str_aux);
			lista->data = ft_strdup(str);
			free(str);
		}
		lista = lista->next;
	}
	env_in_array(mini);
}

int	parse_existing_export(t_mini *mini, char **aux)
{
	t_envs	*lista;
	int		exist;

	exist = 0;
	lista = mini->lista_envs;
	while (lista)
	{
		if (ft_strncmp(aux[0], lista->name, ft_strlen(lista->name)) == 0)
		{
			exist = 1;
			free(lista->data);
			lista->data = ft_strdup(aux[1]);
			free_str(aux);
		}
		lista = lista->next;
	}
	return (exist);
}
