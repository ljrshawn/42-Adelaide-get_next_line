/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:29:30 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/25 17:04:44 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*str_join_free(char *res, char *rem, int fun)
{
	char	*result;
	int		i;
	int		j;

	i = get_str_len(res);
	j = BS;
	if (fun == 1)
	{
		result = str_join(res, rem, i, j);
		if (i != 0)
			free(res);
		return (result);
	}
	else
	{
		if (res == NULL)
			return (NULL);
		result = malloc((i + 1) * sizeof(char));
		if (result != NULL)
			copy_buffer(result, res, i);
		return (result);
	}
}

static char	*read_new(int fd)
{
	ssize_t	bytes_read;
	char	*read_buffer;
	int		n;

	read_buffer = malloc((BS + 1) * sizeof(char));
	if (read_buffer == NULL)
		return (NULL);
	n = BS;
	while (n > 0)
	{
		read_buffer[n] = '\0';
		n--;
	}
	bytes_read = read(fd, read_buffer, BS);
	if (bytes_read <= 0)
	{
		free(read_buffer);
		if (bytes_read == 0)
			return ("");
		return (NULL);
	}
	return (read_buffer);
}

static int	check_new_line(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_end_line(int fd, char *result)
{
	char	*read_buffer;

	read_buffer = read_new(fd);
	if (read_buffer == NULL)
		return (NULL);
	if (*read_buffer == '\0')
		return (result);
	while (check_new_line(read_buffer) == -1)
	{
		result = str_join_free(result, read_buffer, 1);
		free(read_buffer);
		read_buffer = read_new(fd);
		if (read_buffer == NULL)
			return (NULL);
		if (*read_buffer == '\0')
			return (result);
	}
	result = str_join_free(result, read_buffer, 1);
	free(read_buffer);
	return (result);
}

char	*get_next_line_utils(int fd, char *buffer)
{
	char	*read_buffer;
	char	*result;

	read_buffer = read_new(fd);
	if (read_buffer == NULL)
		return (NULL);
	if (*read_buffer == '\0')
		return (str_join_free(buffer, "", 0));
	result = str_join(buffer, read_buffer,
			get_str_len(buffer), BS);
	if (result == NULL)
		return (NULL);
	free(read_buffer);
	if (check_new_line(result) == -1)
	{
		result = get_end_line(fd, result);
		if (result == NULL)
			return (NULL);
	}
	return (result);
}
