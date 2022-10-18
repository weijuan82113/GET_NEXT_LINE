/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@42studen>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 22:27:19 by wchen             #+#    #+#             */
/*   Updated: 2022/10/18 19:52:23 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char		*line[256];

	if(!line[fd])
		line[fd] = "\0";
	find_return = ft_memchr(line[fd], '\n', ft_strlen(line[fd]));
	if (find_return)
		return (return_save(&line[fd], find_return));
	buf = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	if (fd < 0 || fd > 256 || BUFFER_SIZE < 0 || BUFFER_SIZE > INT_MAX)
		return (free_buf(buf));
	read_byte = read(fd, buf, BUFFER_SIZE);
	if (!read_byte || read_byte < 0)
	{
		free (buf);
		return (return_line(&line[fd]));
	}
	buf[read_byte] = '\0';
	line[fd] = ft_strjoin(line[fd], buf);
	free (buf);
	return (get_next_line(fd));
}

// # include <stdbool.h>

// int main(int ac, char **av) {
// 	size_t i;
//     if (ac != 4) {
//         fprintf(stderr, "invalid argument");
//         return 1;
//     }
//     int fd1 = open(av[1], O_RDONLY);
// 	int fd2 = open(av[2], O_RDONLY);
// 	int fd3 = open(av[3], O_RDONLY);
// 	//printf("fd is %d \n", fd);
//     i = 0;
// 	while (true) {
//         char *s1 = get_next_line(fd1);
// 		char *s2 = get_next_line(fd2);
// 		char *s3 = get_next_line(fd3);
// 		printf("%zu:%s \n",i, s1);
// 		printf("%zu:%s \n",i, s2);
// 		printf("%zu:%s \n",i, s3);
//         if (s1 == NULL || s2 == NULL || s3 == NULL) {
//             break;
//         }
//         free(s1);
// 		free(s2);
// 		free(s3);
// 		i ++;
//     }
// }
