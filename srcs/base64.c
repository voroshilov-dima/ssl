/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_encode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:37:12 by dvoroshy          #+#    #+#             */
/*   Updated: 2018/10/20 12:37:15 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	append_base64_padding(t_ssl *ssl, char *str)
{
	uint64_t	i;
	uint64_t	remainder;

	remainder = ssl->message_len % 3;
	if (remainder)
	{
		ssl->padded = 3 - remainder;
		ssl->final_len = ssl->message_len + ssl->padded;
		ssl->text = (unsigned char *)malloc(sizeof(char) * ssl->final_len);
		ssl->text[ssl->final_len] = 0;
		ft_memcpy(ssl->text, str, ssl->message_len);
		i = 0;
		while (i < ssl->padded)
		{
			ssl->text[ssl->message_len + i] = 0;
			i++;
		}
	}
	else
	{
		ssl->final_len = ssl->message_len;
		ssl->text = (unsigned char *)str;
	}
}

void		base64_processing(t_ssl *ssl, char *str)
{
	int	fd;

	if (ssl->output_fd != -1)
		fd = ssl->output_fd;
	else
		fd = (ssl->flags.output == NULL ?
			1 : open(ssl->flags.output, O_WRONLY | O_CREAT, 0644));
	if (ssl->flags.encode == -1)
	{
		ssl->text = (unsigned char *)str;
		base64_decode(ssl, fd);
	}
	else
	{
		append_base64_padding(ssl, str);
		base64_encode(ssl, fd);
	}
}

static void	base64_usage(void)
{
	ft_printf("base64 [-ed] [-i in_file] [-o out_file]\n"
	"  -e         encodes input\n"
	"  -d         decodes input\n"
	"  -i         input file (default stdin)\n"
	"  -o         output file (default stdout)\n");
	exit(1);
}

void		base64(int argc, char **argv)
{
	t_ssl	ssl;
	int		i;

	init_ssl(&ssl, "base64");
	i = 2;
	while (i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == 'i')
			ssl.flags.input = argv[++i];
		else if (argv[i][0] == '-' && argv[i][1] == 'o')
			ssl.flags.output = argv[++i];
		else if (argv[i][0] == '-' && argv[i][1] == 'd')
			ssl.flags.encode = -1;
		else if (argv[i][0] == '-' && argv[i][1] == 'e')
			continue ;
		else if (argv[i][0] == '-')
			base64_usage();
		else
			ssl.flags.input = argv[i];
		i++;
	}
	base64_processing(&ssl, process_file(&ssl, ssl.flags.input, 0));
	exit(0);
}
