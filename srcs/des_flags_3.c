/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_flags_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 13:42:46 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/22 13:42:47 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	set_input_fd(t_des *des, int argc, char **argv, int *pointer)
{
	struct stat stat_buff;

	if (*pointer + 1 < argc)
	{
		des->input_fd = open(argv[*pointer + 1], O_RDONLY, 0);
		if (des->input_fd == -1)
		{
			ft_printf("Failed to open file %s\n", argv[*pointer + 1]);
			exit(1);
		}
		stat(argv[*pointer + 1], &stat_buff);
		if (S_ISDIR(stat_buff.st_mode))
			print_error_and_exit("Input path is not a file\n");
		*pointer += 2;
	}
	else
		des_usage();
}

void	set_output_fd(t_des *des, int argc, char **argv, int *pointer)
{
	char *file_name;

	if (*pointer + 1 < argc)
	{
		file_name = argv[*pointer + 1];
		des->output_fd = open(file_name, O_WRONLY | O_CREAT, 0644);
		if (des->output_fd == -1)
		{
			ft_printf("Failed to open file %s\n", argv[*pointer + 1]);
			exit(1);
		}
		*pointer += 2;
	}
	else
		des_usage();
}

void	set_salt(t_des *des, int argc, char **argv, int *pointer)
{
	if (*pointer + 1 < argc)
	{
		des->raw_salt = argv[*pointer + 1];
		*pointer += 2;
	}
	else
		des_usage();
}

void	set_printing(t_des *des, int argc, char **argv, int *pointer)
{
	(void)argc;
	(void)argv;
	des->print = TRUE;
	*pointer += 1;
}

void	set_iv(t_des *des, int argc, char **argv, int *pointer)
{
	if (*pointer + 1 < argc)
	{
		des->raw_iv = argv[*pointer + 1];
		*pointer += 2;
	}
	else
		des_usage();
}
