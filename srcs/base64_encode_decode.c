/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_encode_decode.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 15:47:33 by dvoroshy          #+#    #+#             */
/*   Updated: 2018/10/21 15:47:34 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char	i64(char c)
{
	int	i;

	i = 0;
	while (i < 64)
	{
		if (B64[i] == c)
			return ((char)i);
		i++;
	}
	if (c == '=')
		return (-1);
	ft_printf("Invalid character in input stream.\n");
	exit(1);
}

void		base64_decode(t_ssl *ssl, int fd)
{
	uint64_t	i;
	char		decoded;

	i = 0;
	while (ssl->text[i] && ssl->text[i + 1] &&
			ssl->text[i + 2] && ssl->text[i + 3])
	{
		if (ssl->text[i] != '=' && ssl->text[i + 1] != '=')
		{
			decoded = (i64(ssl->text[i]) << 2) | (i64(ssl->text[i + 1]) >> 4);
			write(fd, &decoded, 1);
		}
		if (ssl->text[i + 1] != '=' && ssl->text[i + 2] != '=')
		{
			decoded = (i64(ssl->text[i + 1]) << 4) |
				(i64(ssl->text[i + 2]) >> 2);
			write(fd, &decoded, 1);
		}
		if (ssl->text[i + 2] != '=' && ssl->text[i + 3] != '=')
		{
			decoded = (i64(ssl->text[i + 2]) << 6) | i64(ssl->text[i + 3]);
			write(fd, &decoded, 1);
		}
		i += 4;
	}
}

void		base64_encode(t_ssl *ssl, int fd)
{
	uint64_t	i;
	int			temp;

	i = 0;
	while (i < ssl->final_len)
	{
		write(fd, &(B64[ssl->text[i] >> 2]), 1);
		write(fd, &(B64[((ssl->text[i] & 0x03) << 4) |
			((ssl->text[i + 1] & 0xf0) >> 4)]), 1);
		temp = ((ssl->text[i + 1] & 0x0f) << 2) |
			((ssl->text[i + 2] & 0xc0) >> 6);
		(!temp && ssl->final_len - i <= 3 && ssl->padded == 2 ?
			write(fd, "=", 1) : write(fd, &B64[temp], 1));
		temp = ssl->text[i + 2] & 0x3f;
		(!temp && ssl->final_len - i <= 3 && ssl->padded >= 1 ?
			write(fd, "=", 1) : write(fd, &B64[temp], 1));
		i += 3;
	}
}
