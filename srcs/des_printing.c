/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_printing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:11:40 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/22 12:11:42 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	print_in_hex(char *name, uint8_t *buf, int len)
{
	int	i;

	ft_printf("%s=", name);
	i = 0;
	while (i < len)
		ft_printf("%.2X", buf[i++]);
	ft_printf("\n");
}

void		print_key_salt_iv_in_hex(t_des *des)
{
	print_in_hex("salt", des->salt, 8);
	print_in_hex("key", des->key_in_bytes, 8);
	if (des->mode == CBC)
		print_in_hex("iv", des->iv, 8);
	exit(1);
}

void		print_salted(t_des *des)
{
	write(des->output_fd, "Salted__", 8);
	write(des->output_fd, des->salt, 8);
}

void		print_error_and_exit(char *str)
{
	ft_printf("%s", str);
	exit(1);
}

void		des_usage(void)
{
	ft_printf("usage: ciphername [-ade]\n"
	"\t[-i file] [-v IV] [-k key] [-p password]\n"
	"\t[-pring] [-o file] [-s salt]\n\n"
	"-a                 Perform base64 encoding/decoding\n"
	"-d                 Decrypt the input data\n"
	"-e                 Encrypt the input data (default)\n"
	"-i file            Input file to read from (default stdin)\n"
	"-v IV              IV to use, specified as a hexidecimal string\n"
	"-k key             Key to use, specified as a hexidecimal string\n"
	"-p source          Password source\n"
	"-print             Print out the salt, key and IV used\n"
	"-o file            Output file to write to (default stdout)\n"
	"-s salt            Salt to use, specified as a hexidecimal string\n\n");
	exit(1);
}
