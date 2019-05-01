/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:36:51 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/12 12:36:53 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint8_t g_left_shifts[16] = {
	1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
static uint8_t g_key_before_pc2[16][56];

void	keys_finalization(t_des *des)
{
	uint8_t	i;

	i = 0;
	while (i < 16)
	{
		if (des->dir == ENCRYPT || des->mode == CFB || des->mode == OFB)
			key56_to_key48(g_key_before_pc2[i], des->final_keys[i]);
		else
			key56_to_key48(g_key_before_pc2[i], des->final_keys[15 - i]);
		i++;
	}
}

void	left_shift_subroutine(uint8_t *vec_1, uint8_t *vec_2,
	uint8_t bit_cntr, uint8_t n_bits)
{
	while (bit_cntr < n_bits)
	{
		vec_1[bit_cntr] = vec_2[bit_cntr];
		bit_cntr++;
	}
}

void	left_shift(uint8_t *i_vector, uint8_t n_shifts, uint8_t *o_vector)
{
	uint8_t shift_cntr;
	uint8_t i_vector_tmp[28];
	uint8_t	n_bits;
	uint8_t bit_cntr;

	n_bits = 28;
	bit_cntr = 0;
	left_shift_subroutine(i_vector_tmp, i_vector, bit_cntr, n_bits);
	shift_cntr = 0;
	while (shift_cntr < n_shifts)
	{
		o_vector[n_bits - 1] = i_vector_tmp[0];
		bit_cntr = 1;
		while (bit_cntr < n_bits)
		{
			o_vector[bit_cntr - 1] = i_vector_tmp[bit_cntr];
			bit_cntr++;
		}
		bit_cntr = 0;
		left_shift_subroutine(i_vector_tmp, o_vector, bit_cntr, n_bits);
		shift_cntr++;
	}
}

void	left_shifts_schedule(
	uint8_t key_left[17][28], uint8_t key_right[17][28])
{
	uint8_t	i;

	i = 1;
	while (i <= 16)
	{
		left_shift(key_left[i - 1], g_left_shifts[i - 1], key_left[i]);
		left_shift(key_right[i - 1], g_left_shifts[i - 1], key_right[i]);
		join_halves(g_key_before_pc2[i - 1], 56, key_right[i], key_left[i]);
		i++;
	}
}

void	keys_generator(t_des *des)
{
	uint8_t key_plus[56];
	uint8_t key_left[17][28];
	uint8_t key_right[17][28];

	key64_to_key56(des->key, key_plus);
	split_key_into_halves(key_plus, 56, key_right[0], key_left[0]);
	left_shifts_schedule(key_left, key_right);
	keys_finalization(des);
}
