/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_streaming.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:11:55 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/22 12:11:56 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	des_update(t_des *des, uint8_t *input, uint64_t input_length)
{
	uint64_t i;

	i = 0;
	if (input_length <= 8 - des->buffer_filled)
	{
		ft_memcpy(&des->buffer[des->buffer_filled], &input[0], input_length);
		des->buffer_filled += input_length;
	}
	else
	{
		ft_memcpy(&des->buffer[des->buffer_filled], &input[0],
			8 - des->buffer_filled);
		i = 8 - des->buffer_filled;
		des_preencryption(des, des->buffer);
		while (i + 8 < input_length)
		{
			des_preencryption(des, &input[i]);
			i += 8;
		}
		ft_memcpy(&des->buffer[0], &input[i], input_length - i);
		des->buffer_filled = input_length - i;
	}
}

void	des_final(t_des *des)
{
	uint8_t padding;
	uint8_t i;

	i = 0;
	if (des->dir == ENCRYPT)
	{
		if (des->buffer_filled == 8)
		{
			padding = 8;
			des_preencryption(des, des->buffer);
		}
		else
			padding = 8 - des->buffer_filled;
		if (des->mode != CFB)
			while (i < padding)
			{
				des->buffer[des->buffer_filled + i] = padding;
				i++;
			}
	}
	des->last_block = TRUE;
	des_preencryption(des, des->buffer);
}
