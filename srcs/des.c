/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:36:30 by dvoroshy          #+#    #+#             */
/*   Updated: 2018/10/21 17:36:31 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	des_ecb(int argc, char **argv)
{
	t_des	des;

	des_init(&des);
	des.mode = ECB;
	parse_arguments(&des, argc, argv);
	if (des.base64)
		create_pipe(&des);
	if (des.raw_key == NULL)
		generate_key(&des);
	else
		parse_raw_key(&des);
	keys_generator(&des);
	if (des.print)
		print_key_salt_iv_in_hex(&des);
	if (des.salted)
		print_salted(&des);
	processing_routine(&des);
}

void	des_cbc(int argc, char **argv)
{
	t_des	des;

	des_init(&des);
	des.mode = CBC;
	parse_arguments(&des, argc, argv);
	if (des.base64)
		create_pipe(&des);
	if (des.raw_key == NULL)
		generate_key(&des);
	else
	{
		parse_raw_key(&des);
		if (des.raw_iv == NULL)
			print_error_and_exit("iv undefined\n");
	}
	if (des.raw_iv)
		raw_iv_to_iv(&des);
	keys_generator(&des);
	if (des.print)
		print_key_salt_iv_in_hex(&des);
	if (des.salted)
		print_salted(&des);
	processing_routine(&des);
}

void	des_cfb(int argc, char **argv)
{
	t_des	des;

	des_init(&des);
	des.mode = CFB;
	parse_arguments(&des, argc, argv);
	if (des.base64)
		create_pipe(&des);
	if (des.raw_key == NULL)
		generate_key(&des);
	else
	{
		parse_raw_key(&des);
		if (des.raw_iv == NULL)
			print_error_and_exit("iv undefined\n");
	}
	if (des.raw_iv)
		raw_iv_to_iv(&des);
	keys_generator(&des);
	if (des.print)
		print_key_salt_iv_in_hex(&des);
	if (des.salted)
		print_salted(&des);
	processing_routine(&des);
}

void	des_ofb(int argc, char **argv)
{
	t_des	des;

	des_init(&des);
	des.mode = OFB;
	parse_arguments(&des, argc, argv);
	if (des.base64)
		create_pipe(&des);
	if (des.raw_key == NULL)
		generate_key(&des);
	else
	{
		parse_raw_key(&des);
		if (des.raw_iv == NULL)
			print_error_and_exit("iv undefined\n");
	}
	if (des.raw_iv)
		raw_iv_to_iv(&des);
	keys_generator(&des);
	if (des.print)
		print_key_salt_iv_in_hex(&des);
	if (des.salted)
		print_salted(&des);
	processing_routine(&des);
}
