/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 05:39:51 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/02/18 18:29:48 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_gnl_free(void *buffer, char **handler)
{
	if (!buffer)
		return ;
	free(buffer);
	*handler = NULL;
}

int	foundline(char *str)
{
	while (*str)
	{
		if (*(str++) == '\n')
			return (1);
	}
	return (0);
}

int	set_buffer(int fd, char **buffer)
{
	int	readed;
	int	read_count;
	int	i;

	i = 0;
	readed = 1;
	read_count = 0;
	if (ft_strlen(*buffer))
		return (1);
	while (readed > 0 && read_count + BUFFER_SIZE < U_BUFFER_SIZE + 1)
	{
		readed = read(fd, (*buffer) + read_count, BUFFER_SIZE);
		read_count += readed;
		if (readed > 0 && foundline((*buffer) + i))
			return (readed);
		i = read_count;
	}
	if (readed == -1)
		ft_gnl_free(*buffer, buffer);
	return (readed);
}

char	*fetch_line(char *buffer, char *curr_line, int *is_found)
{
	int		linelenght;
	int		i;
	char	*new_line;
	char	*full_line;

	i = 0;
	new_line = NULL;
	full_line = NULL;
	if (lnlen(buffer, &linelenght) > 0)
		new_line = (char *)(malloc(linelenght + 1));
	if (!new_line)
		return (curr_line);
	while (i < linelenght)
	{
		new_line[i] = buffer[i];
		i++;
	}
	new_line[i] = '\0';
	ft_cut_thread(buffer, buffer + linelenght);
	if (i > 0 && new_line[i - 1] == '\n')
		*is_found = 1;
	full_line = ft_strjoin(curr_line, new_line);
	ft_gnl_free(new_line, &new_line);
	ft_gnl_free(curr_line, &curr_line);
	return (full_line);
}

char	*get_next_line(int fd)
{
	int			line_is_found;
	int			read_bytes;
	static char	*read_buffer[OPEN_MAX];
	char		*line;

	line = NULL;
	line_is_found = 0;
	read_bytes = 1;
	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) == -1)
	{
		ft_gnl_free(read_buffer[fd], &read_buffer[fd]);
		return (NULL);
	}
	if (!gnl_allocat(&read_buffer[fd]))
		return (NULL);
	while (read_bytes > 0 && !line_is_found)
	{
		read_bytes = set_buffer(fd, &read_buffer[fd]);
		line = fetch_line(read_buffer[fd], line, &line_is_found);
	}
	if (read_bytes == 0 && !read_buffer[fd][0])
		ft_gnl_free(read_buffer[fd], &read_buffer[fd]);
	return (line);
}
