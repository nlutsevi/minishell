/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlutsevi <nlutsevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 19:09:59 by pperea-d          #+#    #+#             */
/*   Updated: 2021/07/28 17:41:46 by nlutsevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	ptr = (char *)malloc(sizeof(*s1) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		ptr[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		ptr[j++] = s2[i];
		i++;
	}
	ptr[j] = 0;
	return (ptr);
}
