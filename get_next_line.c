/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@42studen>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 22:27:19 by wchen             #+#    #+#             */
/*   Updated: 2022/10/16 15:02:19 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*return_save(char **line, char *find_return)
{
	char	*ret_chr;
	size_t	ret_length;
	size_t	i;

	ret_length = 0;
	while ((*line)[ret_length] != '\n')
		ret_length ++;
	ret_chr = (char *)malloc(sizeof(char) * (ret_length + 1));
	if (!ret_chr)
		return (NULL);
	i = 0;
	while ((*line)[i] != '\n')
	{
		ret_chr[i] = (*line)[i];
		i ++;
	}
	ret_chr[i ++] = '\n';
	ret_chr[i] = '\0';
	free(*line);
	if (*(find_return + 1) != '\0')
		*line = ft_strjoin("\0", find_return + 1);
	else
		*line = "\0";
	return (ret_chr);
}

char	*free_buf(char *buf)
{
	free (buf);
	return (NULL);
}

char	*return_line(char **line)
{
	char	*ret_chr;

	if (**line != '\0')
	{
		ret_chr = ft_strjoin(*line, "\0");
		*line = "\0";
		return (ret_chr);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	ssize_t			read_byte;
	char			*buf;
	char			*find_return;
	static char		*line = "\0";

	find_return = ft_memchr(line, '\n', ft_strlen(line));
	if (find_return)
		return (return_save(&line, find_return));
	buf = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	if (fd < 0 || fd > 256 || BUFFER_SIZE < 0 || BUFFER_SIZE > INT_MAX)
		return (free_buf(buf));
	read_byte = read(fd, buf, BUFFER_SIZE);
	if (!read_byte || read_byte < 0)
	{
		free (buf);
		return (return_line(&line));
	}
	buf[read_byte] = '\0';
	line = ft_strjoin(line, buf);
	free (buf);
	return (get_next_line(fd));
}

// # include <stdbool.h>

// int main(int ac, char **av) {
// 	size_t i;
//     if (ac != 2) {
//         fprintf(stderr, "invalid argument");
//         return 1;
//     }
// 	(void)av;
//     int fd = open("41_with_nl", O_RDONLY);
// 	//printf("fd is %d \n", fd);
//     i = 0;
// 	while (true) {
//         char *s = get_next_line(fd);
// 		printf("%zu:%s",i, s);
//         if (s == NULL) {
//             break;
//         }
//         //printf("%s", s);
//         free(s);
// 		i ++;
//     }
// }
