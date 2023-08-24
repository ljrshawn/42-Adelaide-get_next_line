/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:29:20 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/25 17:05:00 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_str_len(char *c)
{
	int	size;

	if (c == NULL)
		return (0);
	size = 0;
	while (c[size] != '\0')
		size++;
	return (size);
}

void	copy_buffer(char *res, char *readBuffer, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		res[j] = readBuffer[j];
		j++;
	}
	res[j] = '\0';
}

char	*str_join(char *res, char *rem, int i, int j)
{
	int		k;
	char	*s;

	s = malloc((i + j + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	k = 0;
	while (k < i)
	{
		s[k] = res[k];
		k++;
	}
	k = 0;
	while (rem[k] && k < j)
	{
		s[k + i] = rem[k];
		k++;
	}
	s[k + i] = '\0';
	return (s);
}

char	*get_buffer(char *str)
{
	int		i;
	int		size;
	char	*result;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	if (str[i] != '\0')
	{
		size = i;
		while (str[size] != '\0')
			size++;
		result = malloc((size - i + 1) * sizeof(char));
		if (result != NULL)
			copy_buffer(result, str + i, size - i);
	}
	else
		result = NULL;
	return (result);
}

char	*get_next_line(int fd)
{
	char		*result;
	static char	*buffer;
	int			i;

	result = get_next_line_utils(fd, buffer);
	if (buffer != NULL)
		free(buffer);
	if (result == NULL)
	{
		buffer = NULL;
		return (NULL);
	}
	buffer = get_buffer(result);
	i = 0;
	while (result[i] != '\n' && result[i] != '\0')
		i++;
	if (result[i] == '\n')
	{
		i++;
		result[i] = '\0';
	}
	return (result);
}

// #include <stdio.h>
// #include <fcntl.h>

// int main() {
// 	int fd;
// 	char	*str;

// 	fd = open("../tester/getnextline/example.txt", O_RDONLY);
// 	if (fd == -1) {
// 		perror("Failed to open the file");
// 		return 1;
// 	}
// 	while ((str = get_next_line(fd))) {
// 		printf("%s", str);
// 	}
// 	// printf("%s\n", get_next_line(fd));
// 	// printf("next:   %s\n", get_next_line(fd));
// 	close(fd);
// 	return (0);
// }
