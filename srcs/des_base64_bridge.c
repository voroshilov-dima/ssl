/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_base64_bridge.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:10:01 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/22 12:10:02 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		perform_base64_encoding(t_des *des)
{
	t_ssl	ssl;
	t_read	rd;
	char	*file_content;

	init_ssl(&ssl, "base64");
	ssl.output_fd = des->output_fd;
	rd.fd = des->pipe[0];
	rd.length = 0;
	file_content = reading_routine(&rd);
	ssl.message_len = rd.length;
	base64_processing(&ssl, file_content);
}

void		perform_base64_decoding(t_des *des)
{
	t_ssl	ssl;
	t_read	rd;
	char	*file_content;

	init_ssl(&ssl, "base64");
	ssl.output_fd = des->pipe[1];
	rd.fd = des->input_fd;
	rd.length = 0;
	ssl.flags.encode = -1;
	file_content = reading_routine(&rd);
	ssl.message_len = rd.length;
	base64_processing(&ssl, file_content);
}

void		create_encryption_pipe(t_des *des)
{
	pid_t	childpid;

	if (pipe(des->pipe) < 0)
		exit(1);
	if ((childpid = fork()) == -1)
	{
		perror("fork");
		exit(1);
	}
	if (childpid == 0)
	{
		close(des->pipe[0]);
		des->output_fd = des->pipe[1];
	}
	else
	{
		close(des->pipe[1]);
		perform_base64_encoding(des);
		exit(0);
	}
}

static void	create_decryption_pipe(t_des *des)
{
	pid_t	childpid;

	if (pipe(des->pipe) < 0)
		exit(1);
	if ((childpid = fork()) == -1)
	{
		perror("fork");
		exit(1);
	}
	if (childpid == 0)
	{
		close(des->pipe[0]);
		perform_base64_decoding(des);
		exit(1);
	}
	else
	{
		close(des->pipe[1]);
		des->input_fd = des->pipe[0];
	}
}

void		create_pipe(t_des *des)
{
	if (des->dir == ENCRYPT)
		create_encryption_pipe(des);
	else
		create_decryption_pipe(des);
}
