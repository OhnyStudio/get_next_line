/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsavard <jsavard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:07:18 by jsavard           #+#    #+#             */
/*   Updated: 2022/11/10 14:52:01 by jsavard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_make_word(const char *s, int finish)
{
	char	*temp;

	temp = malloc(sizeof(char) * (finish + 1));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, &s[0], (finish + 1));
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*diff;
	char		*line;
	int			i;

	line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	read(fd, line, BUFFER_SIZE);
	i = 0;
	while (line[i])
	{
		if (!line[i + 1])
		{
			diff = line;
			read(fd, line, BUFFER_SIZE);
			line = ft_strjoin(diff, line);
			i = 0;
		}	
		if (line[i] == '\n')
		{
			if (line[i + 1])
				diff = ft_make_word(&line[i + 1], ft_strlen(line));
			line = ft_make_word(&line[0], i);
			line[++i] = '\0';
			return (line);
		}
		i++;
	}
	return (line);
}
