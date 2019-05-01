/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_flags_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:10:50 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/22 12:10:51 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	(*process_flags(char *flag_name))(t_des *, int, char **, int *)
{
	t_flags_dt			*flag;
	static t_flags_dt	flags[] = {
		{ "-i", set_input_fd }, { "-o", set_output_fd }, { "-k", set_key },
		{ "-d", set_decrypt_direction }, { "-e", set_encrypt_direction },
		{ "-v", set_iv }, { "-a", set_base64 }, { "-s", set_salt },
		{ "-p", set_password }, { "-print", set_printing }, { NULL, NULL }
	};

	flag = flags;
	while (flag->name != NULL)
	{
		if (ft_strcmp(flag_name, flag->name) == 0)
			return (flag->func);
		flag++;
	}
	return (NULL);
}

void		parse_arguments(t_des *des, int argc, char **argv)
{
	int		i;
	void	(*func_to_call)(t_des *, int, char **, int *);

	i = 2;
	while (i < argc)
	{
		func_to_call = process_flags(argv[i]);
		if (func_to_call == NULL)
		{
			printf("Flag %s is not supported\n", argv[i]);
			exit(0);
		}
		else
			func_to_call(des, argc, argv, &i);
	}
}
