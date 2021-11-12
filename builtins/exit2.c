/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperea-d <pperea-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 23:10:09 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/08/03 04:10:15 by pperea-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_mini *mini, char **cmd)
{
	int	e;
	int	c;

	c = count_exit(cmd);
	if (c > 1)
		e = ft_ismuldig(cmd);
	if (c == 1)
		ft_exc1(mini);
	else if (c == 2)
		ft_exc2(mini, cmd, e);
	else
		ft_exc3(mini, cmd, e);
}

void	ft_exit2(t_mini *mini)
{
	(void)mini;
	printf("%s\n", "exit");
	exit(0);
}
