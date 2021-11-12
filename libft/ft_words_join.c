/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words_join.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlutsevi <nlutsevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 01:03:06 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/07/28 17:42:23 by nlutsevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

int	count_words(char **words)
{
	int	i;

	i = 0;
	while (words[i])
		i++;
	return (i);
}

char	**ft_words_join(char **words_list, char *new_word)
{
	int		i;
	char	**aux;

	if (words_list == NULL)
	{
		aux = malloc(sizeof(char *) * 2);
		aux[0] = ft_strdup(new_word);
		aux[1] = NULL;
	}
	else
	{
		aux = malloc(sizeof(char *) * (count_words(words_list) + 2));
		i = 0;
		while (i < count_words(words_list))
		{
			aux[i] = ft_strdup(words_list[i]);
			free(words_list[i]);
			i++;
		}
		aux[i] = ft_strdup(new_word);
		aux[i + 1] = NULL;
	}
	return (aux);
}
