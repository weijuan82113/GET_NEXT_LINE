/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@42studen>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 22:27:19 by wchen             #+#    #+#             */
/*   Updated: 2022/10/15 20:34:43 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_save(char *line, char *find_return)
{
	char	*ret_chr = NULL;
	size_t	ret_length;
	size_t	i;

	ret_length = (size_t)(find_return - line + 1);
	ret_chr = (char *)malloc(sizeof(char) * (ret_length + 2));
	if (!ret_chr)
		return (NULL);
	i = 0;
	while (line[i] != '\n')
	{
		ret_chr[i] = line[i];
		i ++;
	}
	//if (*line != '\0')
	free (line);
	ret_chr[i ++] = '\n';
	ret_chr[i] = '\0';
	return (ret_chr);
}

char	*free_buf(char* buf)
{
	free (buf);
	return (NULL);
}

char	*get_next_line(int fd)
{
	ssize_t			read_byte;
	char			*buf;
	char			*find_return;
	char			*ret_chr;
	static char		*line = "\0";

	find_return = ft_memchr((char *)line, '\n', ft_strlen(line));
	if (find_return)
	{
		printf("test1");
		ret_chr = ft_save(line, find_return);
		line = find_return + 1;
		return (ret_chr);
	}
	buf = (void *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	if (fd < 0 || fd > 256 || BUFFER_SIZE < 0 || BUFFER_SIZE > INT_MAX)
		return (free_buf(buf));
	read_byte = read(fd, buf, BUFFER_SIZE);
	if (!read_byte || read_byte < 0)
	{
		if (*line != '\0')
		{
			printf("test2");
			ret_chr = malloc(sizeof(char) * (ft_strlen(line) + 1));
			if (!ret_chr)
				return (free_buf(buf));
			ret_chr = ft_strjoin(line, "\0");
			line = "\0";
			free (buf);
			return (ret_chr);
		}
		printf("test3");
		return (free_buf(buf));
	}
	buf[read_byte] = '\0';
	line = ft_strjoin(line, buf);
	free (buf);
	return (get_next_line(fd));
}

# include <stdbool.h>

int main(int ac, char **av) {
	size_t i;
    if (ac != 2) {
        fprintf(stderr, "invalid argument");
        return 1;
    }
	(void)av;
    int fd = open("41_no_nl", O_RDONLY);
	//printf("fd is %d \n", fd);
    i = 0;
	while (true) {
        char *s = get_next_line(fd);
		printf("%zu:%s",i, s);
        if (s == NULL) {
            break;
        }
        printf("%s", s);
        free(s);
		i ++;
    }
}
