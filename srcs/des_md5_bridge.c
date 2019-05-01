/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_md5_bridge.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:11:22 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/22 12:11:23 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	init_md5_standalone(t_md5 *md5)
{
	int	i;

	i = 0;
	md5->state[0] = 0x67452301;
	md5->state[1] = 0xefcdab89;
	md5->state[2] = 0x98badcfe;
	md5->state[3] = 0x10325476;
	while (i < 16)
		md5->x[i++] = 0;
	md5->a = 0;
	md5->b = 0;
	md5->c = 0;
	md5->d = 0;
}

void	parse_md5_results(t_des *des, uint8_t digest[16])
{
	ft_memcpy(des->key_in_bytes, digest, 8);
	if (des->raw_iv == NULL)
		ft_memcpy(des->iv, digest + 8, 8);
}
