/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:25:44 by orhaddao          #+#    #+#             */
/*   Updated: 2024/02/15 16:22:34 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_file_G(int fd, char *tmp)
{
	char	*buffer;
	int		bytes_read;
	char	*new_tmp;

	bytes_read = 1;
	buffer = (char *) ft_calloc_G(BUFFER_SIZE + 1, 1);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(tmp), NULL);
		buffer[bytes_read] = '\0';
		new_tmp = ft_strjoin_G(tmp, buffer);
		if (!new_tmp)
			return (free(buffer), NULL);
		free(tmp);
		tmp = new_tmp;
		if (ft_strchr_G(buffer, '\n'))
			break ;
	}
	return (free (buffer), tmp);
}

char	*get_line_file_G(char *buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	if (buffer[i] == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc_G(sizeof(char), i + 2);
	i = 0;
	while (buffer[i])
	{
		line[i] = buffer[i];
		if (buffer[i] == '\n')
			break ;
		i++;
	}
	return (line);
}

char	*get_next_G(char *buffer)
{
	int		i;
	int		j;
	char	*new_buffer;

	i = 0;
	new_buffer = NULL;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	new_buffer = ft_calloc_G((ft_strlen_G(buffer) - i + 1), 1);
	i++;
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	return (free (buffer), new_buffer);
}

char	*get_next_line_G(int fd)
{
	static char	*buff;
	char		*extracted_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = get_file_G(fd, buff);
	if (!buff)
		return (NULL);
	extracted_line = get_line_file_G(buff);
	buff = get_next_G(buff);
	return (extracted_line);
}
