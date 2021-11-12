/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlutsevi <nlutsevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 18:15:47 by nlutsevi          #+#    #+#             */
/*   Updated: 2021/07/28 17:53:11 by nlutsevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/libft.h"

int	ft_one_line(char **content, char **line)
{
	*line = ft_strdup(*content);
	free(*content);
	*content = NULL;
	return (0);
}

int	get_new_line(char **content, char **line, int numbytes)
{
	char	*temp;
	char	*temp2;

	temp = ft_strchr(*content, '\n');
	if (numbytes < 0)
		return (-1);
	if (numbytes == 0 && !*content)
	{
		*line = ft_strdup("");
		return (0);
	}
	else if (temp)
	{
		*temp = '\0';
		*line = ft_strdup(*content);
		temp2 = ft_strdup(temp + 1);
		free(*content);
		*content = temp2;
		return (1);
	}
	else if ((ft_strchr(*content, '\0')))
	{
		ft_one_line(&*content, &*line);
	}
	return (0);
}

char	*get_new_line_aux(char *content, char *buff)
{
	char			*temp;

	temp = ft_strjoin(content, buff);
	free(content);
	content = temp;
	return (content);
}

int	get_next_line(int fd, char **line)
{
	static char		*content[FD_SIZE];
	char			*buff;	
	int				numbytes;

	buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if ((fd < 0 || line == NULL || BUFF_SIZE < 0 || (!(buff))))
		return (-1);
	numbytes = read(fd, buff, BUFF_SIZE);
	while (numbytes > 0)
	{
		buff[numbytes] = '\0';
		if (!(content[fd]))
			content[fd] = ft_strdup(buff);
		else
			content[fd] = get_new_line_aux(content[fd], buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	buff = NULL;
	return (get_new_line(&content[fd], &*line, numbytes));
}
