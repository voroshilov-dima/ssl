/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_flags_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:10:55 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/22 12:10:57 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	set_base64(t_des *des, int argc, char **argv, int *pointer)
{
	if (*pointer < argc && argv != NULL)
	{
		des->base64 = 1;
		*pointer += 1;
	}
	else
		des_usage();
}

void	set_key(t_des *des, int argc, char **argv, int *pointer)
{
	if (*pointer + 1 < argc)
	{
		des->raw_key = argv[*pointer + 1];
		*pointer += 2;
	}
	else
		des_usage();
}

void	set_decrypt_direction(t_des *des, int argc, char **argv, int *pointer)
{
	(void)argc;
	(void)argv;
	des->dir = DECRYPT;
	*pointer += 1;
}

void	set_encrypt_direction(t_des *des, int argc, char **argv, int *pointer)
{
	(void)argc;
	(void)argv;
	des->dir = ENCRYPT;
	*pointer += 1;
}

void	set_password(t_des *des, int argc, char **argv, int *pointer)
{
	if (*pointer + 1 < argc)
	{
		des->password = argv[*pointer + 1];
		*pointer += 2;
	}
	else
		des_usage();
}
