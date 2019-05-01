/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 18:52:19 by dvoroshy          #+#    #+#             */
/*   Updated: 2018/10/18 18:52:20 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char	*reading_subroutine1(t_read *rd)
{
	int		i;
	char	*file_content;

	i = 0;
	file_content = (char *)malloc(sizeof(char) * (rd->buffer_chars + 1));
	while (i < rd->buffer_chars)
	{
		file_content[i] = rd->buffer[i];
		i++;
	}
	file_content[rd->buffer_chars] = 0;
	rd->length = rd->buffer_chars;
	return (file_content);
}

static void	reading_subroutine2(t_read *rd, char *temp, char *file_content)
{
	int	i;

	i = 0;
	while (i < rd->length)
	{
		temp[i] = file_content[i];
		i++;
	}
	i = 0;
	while (i < rd->buffer_chars)
	{
		temp[rd->length + i] = rd->buffer[i];
		i++;
	}
}

char		*reading_routine(t_read *rd)
{
	int		i;
	char	*temp;
	char	*file_content;

	ft_bzero(rd->buffer, BUFFER_SIZE);
	file_content = 0;
	while ((i = read(rd->fd, rd->buffer, BUFFER_SIZE)))
	{
		rd->buffer_chars = i;
		if (file_content == 0)
			file_content = reading_subroutine1(rd);
		else
		{
			temp = (char *)malloc(sizeof(char) * (rd->length
				+ rd->buffer_chars + 1));
			reading_subroutine2(rd, temp, file_content);
			temp[rd->length + rd->buffer_chars] = 0;
			free(file_content);
			file_content = temp;
			rd->length += rd->buffer_chars;
		}
	}
	return (file_content);
}

char		*process_file(t_ssl *ssl, char *file_name, int flag)
{
	t_read	rd;
	char	*file_content;

	if (flag)
		ssl->flags.print = 1;
	if (file_name == NULL)
	{
		ssl->flags.quiet = 1;
		rd.fd = 0;
	}
	else if ((rd.fd = open(file_name, O_RDONLY, 0)) < 0)
	{
		ft_printf("Failed to open file\n");
		exit(1);
	}
	rd.length = 0;
	file_content = reading_routine(&rd);
	close(rd.fd);
	ssl->message_len = rd.length;
	ssl->input_type = FILE;
	ssl->input_name = file_name;
	return (file_content);
}
