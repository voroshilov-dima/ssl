/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_modes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:13:44 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/25 14:13:45 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	cbc_mode(t_des *des, uint8_t *message_8_bytes,
	uint8_t *g_result_in_bytes)
{
	if (des->dir == ENCRYPT)
	{
		xor_in_bytes(message_8_bytes, des->iv, 8);
		des_encryption(des, message_8_bytes);
		ft_memcpy(des->iv, g_result_in_bytes, 8);
	}
	else
	{
		des_encryption(des, message_8_bytes);
		xor_in_bytes(g_result_in_bytes, des->iv, 8);
		ft_memcpy(des->iv, message_8_bytes, 8);
	}
	if (des->dir == DECRYPT && des->last_block == TRUE)
	{
		write(des->output_fd, g_result_in_bytes, 8 - g_result_in_bytes[7]);
		des->last_block = FALSE;
	}
	else
		write(des->output_fd, g_result_in_bytes, 8);
}

void	cfb_mode(t_des *des, uint8_t *message_8_bytes,
	uint8_t *g_result_in_bytes)
{
	if (des->dir == ENCRYPT)
	{
		des_encryption(des, des->iv);
		xor_in_bytes(g_result_in_bytes, message_8_bytes, 8);
		ft_memcpy(des->iv, g_result_in_bytes, 8);
	}
	else if (des->dir == DECRYPT)
	{
		des_encryption(des, des->iv);
		ft_memcpy(des->iv, message_8_bytes, 8);
		xor_in_bytes(g_result_in_bytes, message_8_bytes, 8);
	}
	if (des->dir == DECRYPT && des->last_block == TRUE)
	{
		write(des->output_fd, g_result_in_bytes, des->buffer_filled);
		des->last_block = FALSE;
	}
	else if (des->dir == ENCRYPT && des->last_block == TRUE)
	{
		write(des->output_fd, g_result_in_bytes, des->buffer_filled);
		des->last_block = FALSE;
	}
	else
		write(des->output_fd, g_result_in_bytes, 8);
}

void	ofb_mode(t_des *des, uint8_t *message_8_bytes,
	uint8_t *g_result_in_bytes)
{
	if (des->dir == ENCRYPT)
	{
		des_encryption(des, des->iv);
		ft_memcpy(des->iv, g_result_in_bytes, 8);
		xor_in_bytes(g_result_in_bytes, message_8_bytes, 8);
	}
	else if (des->dir == DECRYPT)
	{
		des_encryption(des, des->iv);
		ft_memcpy(des->iv, g_result_in_bytes, 8);
		xor_in_bytes(g_result_in_bytes, message_8_bytes, 8);
	}
	if (des->dir == DECRYPT && des->last_block == TRUE)
	{
		write(des->output_fd, g_result_in_bytes, des->buffer_filled);
		des->last_block = FALSE;
	}
	else if (des->dir == ENCRYPT && des->last_block == TRUE)
	{
		write(des->output_fd, g_result_in_bytes, des->buffer_filled);
		des->last_block = FALSE;
	}
	else
		write(des->output_fd, g_result_in_bytes, 8);
}

void	ecb_mode(t_des *des, uint8_t *message_8_bytes,
	uint8_t *g_result_in_bytes)
{
	des_encryption(des, message_8_bytes);
	if (des->dir == DECRYPT && des->last_block == TRUE)
	{
		write(des->output_fd, g_result_in_bytes, 8 - g_result_in_bytes[7]);
		des->last_block = FALSE;
	}
	else
		write(des->output_fd, g_result_in_bytes, 8);
}
