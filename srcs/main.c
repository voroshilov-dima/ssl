/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 14:44:47 by dvoroshy          #+#    #+#             */
/*   Updated: 2018/10/18 14:44:48 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	main(int argc, char **argv)
{
	static t_main_dt	algorithms[] = {
		{ "md5", md5 }, { "sha256", sha256 }, { "base64", base64 },
		{ "des", des_cbc }, { "des-cbc", des_cbc }, { "des-ecb", des_ecb },
		{ "des-cfb", des_cfb }, { "des-ofb", des_ofb }, { NULL, NULL }
	};
	t_main_dt			*algorithm;

	if (argc < 2)
		ft_printf("Program supports following algorithms: md5, sha256, "
			"base64, des-ecb, des-cbc, des-cfb, des-ctr, des-ofb\n");
	else
	{
		algorithm = algorithms;
		while (algorithm->name != NULL)
		{
			if (ft_strcmp(argv[1], algorithm->name) == 0)
			{
				algorithm->func(argc, argv);
				exit(0);
			}
			algorithm++;
		}
		algorithm_not_found(argv[1]);
	}
}
