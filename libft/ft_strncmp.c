/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlutsevi <nlutsevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 15:35:31 by pperea-d          #+#    #+#             */
/*   Updated: 2021/07/27 01:22:11 by nlutsevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	size_t				j;
	const unsigned char	*ss1;
	const unsigned char	*ss2;

	i = 0;
	j = 0;
	ss1 = (const unsigned char *)s1;
	ss2 = (const unsigned char *)s2;
	if (n == 0)
		return (j);
	if (!s1 || !s2)
		return (0);
	while ((ss1[i] == ss2[i] && ss1[i] != '\0' && i < n))
		i++;
	if (i == n)
		i--;
	j = ss1[i] - ss2[i];
	return (j);
}
