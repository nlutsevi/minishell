/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperea-d <pperea-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 02:08:02 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/03 03:54:02 by pperea-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	check_double_quotes_df(int *dq, char *trimed)
{
	int	i;

	i = 0;
	while (trimed[i])
	{
		if (trimed[i] == '"')
		{
			i++;
			while (trimed[i])
			{
				if (trimed[i] == '"')
					*dq = 1;
				i++;
			}
		}
		if (trimed[i] != '\0')
			i++;
	}
}

void	check_simple_quotes_df(int *sq, char *trimed)
{
	int	i;

	i = 0;
	while (trimed[i])
	{
		if (trimed[i] == '\'')
		{
			i++;
			while (trimed[i])
			{
				if (trimed[i] == '\'')
					*sq = 1;
				i++;
			}
		}
		if (trimed[i] != '\0')
			i++;
	}
}

char	**trimed_without_quotes(char *trimed, char **files, int dq, int sq)
{
	files = ft_split(trimed, ' ');
	if (dq)
		files = skip_doubleq(files);
	if (sq)
		files = skip_simpleq(files);
	return (files);
}

char	**ft_double_files(t_mini *mini, char *str, int k)
{
	char	*trimed;
	char	**files;
	int		i;
	int		dq;
	int		sq;

	dq = 0;
	sq = 0;
	files = NULL;
	trimed = ft_strtrim(str, " ");
	i = 0;
	while (trimed[i])
	{
		if (trimed[i] == ' ')
			mini->double_pipes[k].df = 1;
		i++;
	}
	check_double_quotes_df(&dq, trimed);
	check_simple_quotes_df(&sq, trimed);
	if (mini->double_pipes[k].df == 1)
		files = trimed_without_quotes(trimed, files, dq, sq);
	free(trimed);
	return (files);
}
