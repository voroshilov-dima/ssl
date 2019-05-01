/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_salt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:11:48 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/22 12:11:49 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	validate_raw_salt(char *salt)
{
	int	i;
	int len;

	len = ft_strlen(salt);
	if (len > 16)
		print_error_and_exit(
			"hex string is too long\ninvalid hex salt value\n");
	i = 0;
	while (salt[i])
	{
		if ((salt[i] >= 48 && salt[i] <= 57) ||
			(salt[i] >= 65 && salt[i] <= 70) ||
			(salt[i] >= 97 && salt[i] <= 102))
			i++;
		else
			print_error_and_exit("non-hex digit\ninvalid hex salt value\n");
	}
}

void	generate_salt(t_des *des)
{
	uint8_t	buffer[8];
	int		bytes_read;
	int		fd;
	int		index;

	fd = open("/dev/random", O_RDONLY, 0);
	bytes_read = 0;
	index = 0;
	while ((bytes_read = read(fd, buffer, 8 - index)))
	{
		ft_memcpy(
			des->salt + index,
			buffer,
			(bytes_read + index <= 8 ? bytes_read : 8 - index));
		index += bytes_read;
	}
}

void	read_salt_from_file(t_des *des)
{
	uint8_t	buffer[8];
	int		bytes_read;
	int		index;

	validate_magic_number(des);
	index = 0;
	while ((bytes_read = read(des->input_fd, buffer, 8 - index)))
	{
		ft_memcpy(
			des->salt + index,
			buffer,
			(bytes_read + index <= 8 ? bytes_read : 8 - index));
		index += bytes_read;
	}
}

void	raw_salt_to_salt(t_des *des)
{
	uint64_t	i;
	uint64_t	len;

	validate_raw_salt(des->raw_salt);
	len = ft_strlen((char *)des->raw_salt);
	i = 0;
	while (i < len)
	{
		des->salt[i / 2] = hex_to_number(des->raw_salt[i]) * 16
			+ hex_to_number(des->raw_salt[i + 1]);
		i += 2;
	}
	while (i < 8)
	{
		des->salt[i] = 0;
		i++;
	}
}
