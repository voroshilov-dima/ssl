/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_algorithm_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 12:55:07 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/23 12:55:08 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint8_t g_ip_inv[64] = {
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25};

static uint8_t g_f_output[32] = {0};
static uint8_t g_result_before_ip_inv[64];
static uint8_t g_result[64];
static uint8_t g_result_in_bytes[8];

static uint8_t g_message_left[17][32];
static uint8_t g_message_right[17][32];

void	partition_right_left(u_int8_t *vector, uint8_t length,
	uint8_t *key_right, uint8_t *key_left)
{
	uint8_t i;
	uint8_t half_length;

	i = 0;
	half_length = length / 2;
	while (i < half_length)
	{
		key_left[i] = vector[i];
		key_right[i] = vector[i + half_length];
		i++;
	}
}

void	do_ip_inv(void)
{
	uint8_t i;

	i = 0;
	while (i < 64)
	{
		g_result[i] = g_result_before_ip_inv[g_ip_inv[i] - 1];
		i++;
	}
}

void	des_encryption(t_des *des, uint8_t *message_8_bytes)
{
	uint8_t	i;
	uint8_t message_64_bits[64];

	i = 1;
	bytes_to_bits(message_8_bytes, message_64_bits, 64);
	perform_ip(message_64_bits, g_message_right[0], g_message_left[0]);
	while (i <= 16)
	{
		ft_memcpy(g_message_left[i], g_message_right[i - 1],
			32 * sizeof(g_message_right[i][0]));
		function_f(g_message_right[i - 1], des->final_keys[i - 1], g_f_output);
		xor(g_message_left[i - 1], g_f_output, 32, g_message_right[i]);
		i++;
	}
	join_halves(g_result_before_ip_inv, 64,
		g_message_left[16], g_message_right[16]);
	do_ip_inv();
	bits_to_bytes(g_result, g_result_in_bytes, 8);
}

void	des_preencryption(t_des *des, uint8_t *message_8_bytes)
{
	if (des->mode == ECB)
		ecb_mode(des, message_8_bytes, g_result_in_bytes);
	else if (des->mode == CBC)
		cbc_mode(des, message_8_bytes, g_result_in_bytes);
	else if (des->mode == CFB)
		cfb_mode(des, message_8_bytes, g_result_in_bytes);
	else if (des->mode == OFB)
		ofb_mode(des, message_8_bytes, g_result_in_bytes);
	des->buffer_filled = 0;
}
