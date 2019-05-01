/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:11:09 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/22 12:11:10 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	validate_raw_key(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if ((key[i] >= 48 && key[i] <= 57) ||
			(key[i] >= 65 && key[i] <= 70) ||
			(key[i] >= 97 && key[i] <= 102))
			i++;
		else
			print_error_and_exit("non-hex digit\n");
	}
}

void	parse_raw_key(t_des *des)
{
	int	len_in_bits;

	validate_raw_key(des->raw_key);
	len_in_bits = ft_strlen(des->raw_key) * 4;
	hex_to_bits(
		(uint8_t *)des->raw_key,
		des->key,
		len_in_bits <= 64 ? len_in_bits : 64);
	bits_to_bytes(des->key, des->key_in_bytes, 8);
}

void	generate_key(t_des *des)
{
	if (des->password == NULL)
		get_password(des);
	if (des->dir == ENCRYPT)
	{
		if (des->raw_salt == NULL)
			generate_salt(des);
		else
			raw_salt_to_salt(des);
		des->salted = TRUE;
	}
	else
		read_salt_from_file(des);
	pbkdf(des);
	bytes_to_bits(des->key_in_bytes, des->key, 64);
}
