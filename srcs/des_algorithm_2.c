/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_algorithm_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:39:18 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/22 12:39:19 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint8_t g_ip[64] = {
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7};

static uint8_t g_e_bit_selection[48] = {
	32, 1, 2, 3, 4, 5, 4, 5,
	6, 7, 8, 9, 8, 9, 10, 11,
	12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21,
	22, 23, 24, 25, 24, 25, 26, 27,
	28, 29, 28, 29, 30, 31, 32, 1};

static uint8_t g_p[32] = {
	16, 7, 20, 21, 29, 12, 28, 17,
	1, 15, 23, 26, 5, 18, 31, 10,
	2, 8, 24, 14, 32, 27, 3, 9,
	19, 13, 30, 6, 22, 11, 4, 25};

void	xor(uint8_t *vector1, uint8_t *vector2,
	uint8_t n_elements, uint8_t *vector_res)
{
	uint8_t i;

	i = 0;
	while (i < n_elements)
	{
		if (((vector1[i] == 1) && (vector2[i] == 0)) ||
			((vector1[i] == 0) && (vector2[i] == 1)))
			vector_res[i] = 1;
		else if (((vector1[i] == 1) && (vector2[i] == 1)) ||
			((vector1[i] == 0) && (vector2[i] == 0)))
			vector_res[i] = 0;
		i++;
	}
}

void	do_permutation_p(uint8_t *s_message_right, uint8_t *p_message_right)
{
	uint8_t i;

	i = 0;
	while (i < 32)
	{
		p_message_right[i] = s_message_right[g_p[i] - 1];
		i++;
	}
}

void	perform_ip(uint8_t *message,
	uint8_t *new_message_right, uint8_t *new_message_left)
{
	uint8_t	new_message[64];
	uint8_t	i;

	i = 0;
	while (i < 64)
	{
		new_message[i] = message[g_ip[i] - 1];
		i++;
	}
	partition_right_left(new_message, 64, new_message_right, new_message_left);
}

void	function_e(uint8_t *i_vector, uint8_t *o_vector)
{
	uint8_t i;

	i = 0;
	while (i < 48)
	{
		o_vector[i] = i_vector[g_e_bit_selection[i] - 1];
		i++;
	}
}

void	function_f(uint8_t *message_right, uint8_t *key, uint8_t *g_f_output)
{
	uint8_t e_message_right[48];
	uint8_t k_e_message_right[48];
	uint8_t s_message_right[32];
	uint8_t p_message_right[32];

	ft_memset(e_message_right, 0, 48);
	ft_memset(k_e_message_right, 0, 48);
	ft_memset(s_message_right, 0, 32);
	ft_memset(p_message_right, 0, 32);
	function_e(message_right, e_message_right);
	xor(key, e_message_right, 48, k_e_message_right);
	function_s(k_e_message_right, s_message_right);
	do_permutation_p(s_message_right, p_message_right);
	ft_memcpy(g_f_output, p_message_right, 32 * sizeof(p_message_right[0]));
}
