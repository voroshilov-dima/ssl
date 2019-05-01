/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:17:32 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/22 12:17:33 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint8_t	number_to_hex(uint8_t number)
{
	static char hex_base[16] = {
		'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	int			i;

	i = 0;
	while (i < 16)
	{
		if (i == number)
			return (hex_base[i]);
		i++;
	}
	return (hex_base[i]);
}

int		hex_to_number(uint8_t hex)
{
	static char hex_base[16] = {
		'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	int			i;

	i = 0;
	while (i < 16)
	{
		if (hex_base[i] == ft_toupper(hex))
			return (i);
		i++;
	}
	return (0);
}

void	char_to_uint8_t(uint8_t char_var, uint8_t *bool_vec, uint8_t n_bits)
{
	int i;

	i = 0;
	while (i < n_bits)
	{
		if (char_var % 2 == 0)
			bool_vec[n_bits - i - 1] = 0;
		else
			bool_vec[n_bits - i - 1] = 1;
		char_var = (char_var - (char_var % 2)) / 2;
		i++;
	}
}
