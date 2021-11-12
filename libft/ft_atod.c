/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlutsevi <nlutsevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 16:45:32 by pperea-d          #+#    #+#             */
/*   Updated: 2021/07/27 01:20:29 by nlutsevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

double	decimal(const char *str)
{
	double	dec;
	double	div;

	dec = 0.0;
	div = 0.1;
	while (ft_isdigit(*str))
	{
		dec += div * (*str - '0');
		div /= 10;
		str++;
	}
	return (dec);
}

double	ft_atod(const char *str)
{
	int		sign;
	double	num;

	num = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		num = 10 * num + *str - '0';
		str++;
	}
	if (*str == '.')
		num += decimal(++str);
	return ((double)(sign * num));
}
