/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_pbkdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:11:34 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/22 12:11:35 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char	*concatenate_pass_and_salt(t_ssl *ssl, t_des *des)
{
	char	*str;
	int		pass_len;

	ssl->message_len = (8 + ft_strlen(des->password));
	str = (char *)malloc(sizeof(char) * ssl->message_len);
	pass_len = ft_strlen(des->password);
	ft_memcpy(str, des->password, pass_len);
	ft_memcpy(str + pass_len, des->salt, 8);
	return (str);
}

void		pbkdf(t_des *des)
{
	uint64_t	i;
	t_ssl		ssl;
	t_md5		md5;
	uint8_t		buf[64];
	uint8_t		digest[16];

	init_md5_standalone(&md5);
	init_ssl(&ssl, "md5");
	append_padding(&ssl, concatenate_pass_and_salt(&ssl, des));
	md5_append_length(&ssl);
	i = 0;
	while (i * 64 < ssl.final_len)
	{
		ft_memcpy(buf, ssl.text + i * 64, 64);
		md5_transform(&md5, buf);
		i++;
	}
	words_to_chars_inverse(digest, md5.state, 16);
	parse_md5_results(des, digest);
}
