/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:09:47 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/22 12:18:29 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	bytes_to_bits(uint8_t *bytes, uint8_t *bits, uint64_t n_bits)
{
	uint64_t	i;

	i = 0;
	while (i < n_bits)
	{
		bits[i] = (((128 >> i % 8) & bytes[i / 8]) == 0 ? 0 : 1);
		i++;
	}
}

void	bits_to_bytes(uint8_t *bits, uint8_t *bytes, uint64_t n_bytes)
{
	uint64_t	i;
	uint64_t	j;

	i = 0;
	j = 0;
	while (i < n_bytes)
	{
		j = 0;
		while (j < 8)
		{
			bytes[i] = bytes[i] * 2 + bits[8 * i + j];
			j++;
		}
		i++;
	}
}

void	hex_to_bits(uint8_t *hex, uint8_t *bits, uint64_t n_bits)
{
	uint64_t	i;

	i = 0;
	while (i < n_bits)
	{
		bits[i] = (((8 >> i % 4) & hex_to_number(hex[i / 4])) == 0 ? 0 : 1);
		i++;
	}
}
