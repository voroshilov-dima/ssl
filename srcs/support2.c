/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 14:45:01 by dvoroshy          #+#    #+#             */
/*   Updated: 2018/10/18 14:45:02 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	init_ssl(t_ssl *ssl, char *name)
{
	ssl->name = name;
	ssl->message_len = 0;
	ssl->padded = 0;
	ssl->flags.reverse = 0;
	ssl->flags.quiet = 0;
	ssl->flags.print = 0;
	ssl->flags.input = 0;
	ssl->flags.output = 0;
	ssl->flags.encode = 1;
	ssl->output_fd = -1;
}

void	append_padding(t_ssl *ssl, char *str)
{
	uint64_t	i;

	if (ssl->message_len % 64 < 56)
		ssl->final_len = (ssl->message_len / 64 + 1) * 64;
	else
		ssl->final_len = (ssl->message_len / 64 + 2) * 64;
	ssl->text = (unsigned char *)malloc(sizeof(char) * ssl->final_len);
	ft_memcpy(ssl->text, str, ssl->message_len);
	ssl->text[ssl->message_len] = 128;
	i = ssl->message_len + 1;
	while (i < ssl->final_len - 8)
	{
		ssl->text[i] = 0;
		i++;
	}
}

void	usage(t_ssl *ssl)
{
	ft_printf(
		"%s: illegal option -- -\nusage: %s [-qr] [-s string] [files ...]\n",
		ssl->name, ssl->name);
	exit(1);
}

void	print_results(t_ssl *ssl, unsigned char *str, uint64_t len)
{
	uint64_t i;

	i = 0;
	if (ssl->flags.print == 1 && ssl->message_len > 0)
		while (i < ssl->message_len)
			ft_printf("%c", ssl->text[i++]);
	i = 0;
	if (ssl->flags.quiet == 0 && ssl->flags.reverse == 0 &&
		ssl->flags.print == 0 && ssl->input_type == FILE)
		ft_printf("%s (%s) = ", ssl->name, ssl->input_name);
	else if (ssl->flags.quiet == 0 && ssl->flags.reverse == 0 &&
		ssl->flags.print == 0 && ssl->input_type == STRING)
		ft_printf("%s (\"%s\") = ", ssl->name, ssl->input_name);
	while (i < len)
		ft_printf("%.2x", str[i++]);
	if (ssl->flags.quiet == 0 && ssl->flags.reverse == 1 &&
		ssl->flags.print == 0 && ssl->input_type == FILE)
		ft_printf(" %s", ssl->input_name);
	else if (ssl->flags.quiet == 0 && ssl->flags.reverse == 1 &&
		ssl->flags.print == 0 && ssl->input_type == STRING)
		ft_printf(" \"%s\"", ssl->input_name);
	free(ssl->text);
	init_ssl(ssl, ssl->name);
	ft_printf("\n");
}

char	*process_string(t_ssl *ssl, char **argv, int *i)
{
	char	*str;

	if (argv[*i][2])
		str = argv[*i] + 2;
	else
	{
		*i += 1;
		str = argv[*i];
	}
	if (str == 0)
		usage(ssl);
	ssl->message_len = ssl_strlen(str);
	ssl->input_type = STRING;
	ssl->input_name = str;
	return (str);
}
