/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_encrypt_decrypt.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:10:38 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/22 12:10:40 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	processing_routine(t_des *des)
{
	uint8_t	buffer[16];
	int		bytes_read;

	while ((bytes_read = read(des->input_fd, buffer, 16)))
		des_update(des, buffer, bytes_read);
	des_final(des);
}
