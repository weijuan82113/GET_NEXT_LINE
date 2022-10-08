/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@42studen>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 22:27:19 by wchen             #+#    #+#             */
/*   Updated: 2022/10/09 02:06:40 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_save(char *line, char *find_return)
{
	char	*ret_chr;
	size_t	ret_length;
	size_t	i;

	ret_length = ft_strlen(line) + (size_t)(find_return - line + 1);
	ret_chr = (char *)malloc(sizeof(char) * (ret_length + 2));
	if (!ret_chr)
		return (NULL);
	i = 0;
	while (line[i] != '\n')
	{
		ret_chr[i] = line[i];
		i ++;
	}
	ret_chr[i ++] = '\n';
	ret_chr[i] = '\0';
	return (ret_chr);
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
		ret_chr = ft_save(line, find_return);
		line = find_return + 1;
		//free (line);
		return (ret_chr);
	}
	buf = (void *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE < 0 || BUFFER_SIZE > SIZE_MAX)
		return (NULL);
	read_byte = read(fd, buf, BUFFER_SIZE);
	if (!read_byte)
	{
		if (*line != '\0')
		{
			ret_chr = line;
			line = "\0";
			free (buf);
			return (ret_chr);
		}
		return (NULL);
	}
	buf[BUFFER_SIZE] = '\0';
	line = ft_strjoin(line, buf);
	//printf("line is %s\n", line);
	//free (line);
	free (buf);
	return (get_next_line(fd));
}

// int	main(void)
// {
// 	int 		fd;
// 	char		*print_char;
// 	ssize_t		read_byte;
// 	char		buf[BUFFER_SIZE];

// 	fd = 0;
// 	fd = open("./empty", O_RDWR);
// 	read_byte = read(fd, buf, BUFFER_SIZE);
// 	printf("read_byte is %zd \n", read_byte);
// 	printf("fd is %d \n", fd);
// 	print_char = get_next_line(fd);
// 	while (print_char)
// 	{
// 		printf("print char is %s", print_char);
// 		print_char = get_next_line(fd);
// 	}
// 	close(fd);
// 	return 0;
// }
