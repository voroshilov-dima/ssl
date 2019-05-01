/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:11:02 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/22 12:11:03 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	des_init(t_des *des)
{
	des->dir = ENCRYPT;
	des->bytes_read = 0;
	des->file = NULL;
	des->print = FALSE;
	ft_memset(des->buffer, 0, sizeof(des->buffer));
	des->buffer_filled = 0;
	des->raw_key = NULL;
	ft_memset(des->key, 0, sizeof(des->key));
	ft_memset(des->key_in_bytes, 0, sizeof(des->key_in_bytes));
	des->salted = FALSE;
	des->raw_salt = NULL;
	ft_memset(des->salt, 0, sizeof(des->salt));
	des->raw_iv = NULL;
	ft_memset(des->iv, 0, sizeof(des->iv));
	des->last_block = FALSE;
	des->password = NULL;
	des->input_fd = 0;
	des->output_fd = 1;
	des->base64 = FALSE;
}
