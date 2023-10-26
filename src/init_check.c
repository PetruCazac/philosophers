/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:08:52 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/26 08:04:06 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	ft_isnum(char *arg)
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

static long	transform(const char *s)
{
	int		i;
	long	j;

	j = 0;
	i = 0;
	while (s[i] > 47 && s[i] < 58 && s[i])
	{
		j = j * 10 + (s[i] - 48);
		i++;
	}
	return (j);
}

long	ft_atoi(const char *str)
{
	size_t	i;
	long	j;

	i = 0;
	j = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		j = transform(&str[i + 1]) * (-1);
	if (str[i] == '+')
		j = transform(&str[i + 1]);
	if (str[i] > 47 && str[i] < 58)
		j = transform(&str[i]);
	return (j);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*v;
	char	c;
	size_t	i;

	i = 0;
	c = 0;
	v = malloc(size * count);
	if (!v)
		return (v);
	while (i < (size * count))
	{
		v[i] = c;
		i++;
	}
	return ((void *) v);
}
