/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_iv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:24:25 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/23 11:24:26 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	validate_raw_iv(char *iv)
{
	int	i;
	int len;

	len = ft_strlen(iv);
	if (len > 16)
		print_error_and_exit("hex string is too long\ninvalid hex iv value\n");
	i = 0;
	while (iv[i])
	{
		if ((iv[i] >= 48 && iv[i] <= 57) ||
			(iv[i] >= 65 && iv[i] <= 70) ||
			(iv[i] >= 97 && iv[i] <= 102))
			i++;
		else
			print_error_and_exit("non-hex digit\ninvalid hex iv value\n");
	}
}

void	raw_iv_to_iv(t_des *des)
{
	uint64_t	i;
	uint64_t	len;

	validate_raw_iv(des->raw_iv);
	len = ft_strlen((char *)des->raw_iv);
	i = 0;
	while (i < len)
	{
		des->iv[i / 2] = hex_to_number(des->raw_iv[i]) * 16
			+ hex_to_number(des->raw_iv[i + 1]);
		i += 2;
	}
	while (i < 8)
	{
		des->iv[i] = 0;
		i++;
	}
}
