/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_magic_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:12:23 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/22 18:12:24 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	validate_magic_number(t_des *des)
{
	static uint8_t	magic_number_correct[] = "Salted__";
	uint8_t			magic_number_read[8];
	uint8_t			buffer[8];
	int				bytes_read;
	int				index;

	bytes_read = 0;
	index = 0;
	while ((bytes_read = read(des->input_fd, buffer, 8 - index)))
	{
		ft_memcpy(
			magic_number_read + index, buffer,
			(bytes_read + index <= 8 ? bytes_read : 8 - index));
		index += bytes_read;
	}
	index = 0;
	while (index < 8)
	{
		if (magic_number_read[index] != magic_number_correct[index])
			print_error_and_exit("bad magic number\n");
		index++;
	}
}
