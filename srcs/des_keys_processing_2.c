/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_keys_processing_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 13:47:41 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/22 13:47:43 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint8_t g_pc1[56] = {
	57, 49, 41, 33, 25, 17, 9, 1,
	58, 50, 42, 34, 26, 18, 10, 2,
	59, 51, 43, 35, 27, 19, 11, 3,
	60, 52, 44, 36, 63, 55, 47, 39,
	31, 23, 15, 7, 62, 54, 46, 38,
	30, 22, 14, 6, 61, 53, 45, 37,
	29, 21, 13, 5, 28, 20, 12, 4};

static uint8_t g_pc2[48] = {
	14, 17, 11, 24, 1, 5, 3, 28,
	15, 6, 21, 10, 23, 19, 12, 4,
	26, 8, 16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55, 30, 40,
	51, 45, 33, 48, 44, 49, 39, 56,
	34, 53, 46, 42, 50, 36, 29, 32};

void	key64_to_key56(uint8_t *key, uint8_t *new_key)
{
	uint8_t i;

	i = 0;
	while (i < 56)
	{
		new_key[i] = key[g_pc1[i] - 1];
		i++;
	}
}

void	key56_to_key48(uint8_t *key, uint8_t *new_key)
{
	uint8_t i;

	i = 0;
	while (i < 48)
	{
		new_key[i] = key[g_pc2[i] - 1];
		i++;
	}
}

void	split_key_into_halves(
	uint8_t *vector, uint8_t length, uint8_t *key_right, uint8_t *key_left)
{
	int i;
	int half_of_length;

	i = 0;
	half_of_length = length / 2;
	while (i < half_of_length)
	{
		key_left[i] = vector[i];
		key_right[i] = vector[i + half_of_length];
		i++;
	}
}
