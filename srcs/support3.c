/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:16:17 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/22 12:16:18 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	print_vector(uint8_t *ip, uint8_t length)
{
	uint8_t i;

	i = 0;
	while (i < length)
	{
		printf("%d", *(ip + i));
		i++;
	}
	printf("\n");
}

void	join_halves(
	uint8_t *vector, uint8_t length, uint8_t *key_right, uint8_t *key_left)
{
	int i;
	int half_of_length;

	i = 0;
	half_of_length = length / 2;
	while (i < half_of_length)
	{
		vector[i] = key_left[i];
		vector[i + half_of_length] = key_right[i];
		i++;
	}
}

void	algorithm_not_found(char *str)
{
	ft_printf("ft_ssl: Error: %s is invalid command", str);
	ft_printf("\nStandard commands:\n\nMessage Digest commands:\n");
	ft_printf("md5\nsha256\n\n");
	ft_printf("Cipher commands:\nbase64\ndes\ndes-ecb\n"
		"des-cbc\ndes-cfb\ndes-ctr\ndes-ofb\n");
	exit(1);
}

void	xor_in_bytes(uint8_t *a, uint8_t *b, uint8_t len)
{
	uint8_t	i;

	i = 0;
	while (i < len)
	{
		a[i] = a[i] ^ b[i];
		i++;
	}
}
