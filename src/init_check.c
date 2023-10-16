/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:08:52 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/16 17:18:24 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	ft_isnum(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (printf("Not a number!\n"), false);
		i++;
	}
	if (i > 6)
		return (printf("Number too long\n"), false);
	return (true);
}

bool	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 6 && argc != 5)
		return (false);
	while (i < argc)
	{
		if (!ft_isnum(argv[i]))
			return (false);
		i++;
	}
	return (true);
}
