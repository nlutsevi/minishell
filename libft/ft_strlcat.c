/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlutsevi <nlutsevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 17:14:41 by pperea-d          #+#    #+#             */
/*   Updated: 2021/07/27 01:22:01 by nlutsevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		f;
	int		i;
	int		t;
	int		len1;
	int		len2;

	i = 0;
	if (!dst || !src)
		return (0);
	len2 = ft_strlen(src);
	if (size == 0)
		return (len2 + (int)size);
	len1 = ft_strlen(dst);
	t = len1 + len2;
	if ((int)size <= len1)
		return (len2 + (int)size);
	f = (int)size - len1 - 1;
	while (f-- > 0 && src[i] != '\0')
		dst[len1++] = src[i++];
	dst[len1] = '\0';
	return (t);
}
