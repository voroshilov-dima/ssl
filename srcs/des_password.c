/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_password.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:11:29 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/04/22 12:11:30 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	get_password(t_des *des)
{
	char	*temp;
	int		len;
	char	password_initial[128];
	char	password_confirmed[128];

	temp = getpass("enter des-ecb encryption password:");
	ft_strcpy(password_initial, temp);
	len = ft_strlen(temp);
	if (len == 0)
		exit(0);
	if (des->dir == ENCRYPT)
	{
		ft_strcpy(password_confirmed,
		getpass("Verifying - enter des-ecb encryption password:"));
		if (ft_strcmp(password_initial, password_confirmed))
			print_error_and_exit("Verify failure\nbad password read\n");
	}
	des->password = password_initial;
}
