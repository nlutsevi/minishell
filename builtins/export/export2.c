/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperea-d <pperea-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 21:16:16 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/07/28 04:21:22 by pperea-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**manage_doubleq(char *str)
{
	char	*aux;
	char	**cmd;
	char	*aux2;

	aux = char_to_str('"');
	cmd = ft_split(str, '=');
	free(str);
	aux2 = cmd[0];
	cmd[0] = ft_strtrim(aux2, aux);
	free(aux2);
	aux2 = cmd[0];
	cmd[0] = ft_strjoin(aux2, "=\"");
	free(aux2);
	aux2 = cmd[0];
	cmd[0] = ft_strjoin(aux2, cmd[1]);
	free(aux2);
	free(cmd[1]);
	cmd[1] = NULL;
	free(aux);
	return (cmd);
}

char	**manage_simpleq(char *str)
{
	char	*aux;
	char	**cmd;
	char	*aux2;

	aux = char_to_str('\'');
	cmd = ft_split(str, '=');
	free(str);
	aux2 = cmd[0];
	cmd[0] = ft_strtrim(aux2, aux);
	free(aux2);
	aux2 = cmd[1];
	cmd[1] = ft_strtrim(aux2, aux);
	free(aux2);
	aux2 = cmd[0];
	cmd[0] = ft_strjoin(aux2, "=\"");
	free(aux2);
	aux2 = cmd[0];
	cmd[0] = ft_strjoin(aux2, cmd[1]);
	free(aux2);
	aux2 = cmd[0];
	cmd[0] = ft_strjoin(aux2, "\"");
	free(aux2);
	free(aux);
	return (cmd);
}

void	run_export_aux(t_mini *mini, char *str)
{
	int	i;

	i = 0;
	mini->export_equal = 0;
	mini->export_data_null = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			mini->export_equal = 1;
			if (str[i + 1] == '\0')
				mini->export_data_null = 1;
		}
		i++;
	}
}

char	**manage_equal(char **aux, char *str)
{
	aux = malloc(sizeof(char *) * 2);
	aux[0] = ft_strdup(str);
	aux[1] = NULL;
	return (aux);
}

char	**manage_data_null(char **aux, char *str)
{
	aux = malloc(sizeof(char *) * 2);
	aux[0] = ft_strtrim(str, "=\0");
	aux[1] = ft_strdup("\"\"");
	return (aux);
}
