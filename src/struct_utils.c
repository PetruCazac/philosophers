/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 09:13:08 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/25 22:42:46 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static long	transform(const char *s);
static int	ft_isspace(char str);

long	ft_atoi(const char *str)
{
	size_t	i;
	long	j;

	i = 0;
	j = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		j = transform(&str[i + 1]) * (-1);
	if (str[i] == '+')
		j = transform(&str[i + 1]);
	if (str[i] > 47 && str[i] < 58)
		j = transform(&str[i]);
	return (j);
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

static int	ft_isspace(char str)
{
	if (str == 32 || (str >= 9 && str <= 13))
		return (1);
	else
		return (0);
}

bool	initialize_mutex(t_param **param)
{
	if (pthread_mutex_init((*param)->dead_fork, NULL))
	{
		pthread_mutex_destroy((*param)->dead_fork);
		return (false);
	}
	if (pthread_mutex_init((*param)->print_fork, NULL))
	{
		pthread_mutex_destroy((*param)->print_fork);
		return (false);
	}
	if (pthread_mutex_init((*param)->time_fork, NULL))
	{
		pthread_mutex_destroy((*param)->time_fork);
		return (false);
	}
	return (true);
}

bool	allocate_mutexes(t_param **param)
{
	(*param)->dying = ft_calloc(1, sizeof(pthread_t));
	if (!(*param)->dying)
		return (false);
	(*param)->dead_fork = ft_calloc(1, sizeof(pthread_mutex_t));
	if (!(*param)->dead_fork)
		return (false);
	(*param)->print_fork = ft_calloc(1, sizeof(pthread_mutex_t));
	if (!(*param)->print_fork)
		return (false);
	(*param)->time_fork = ft_calloc(1, sizeof(pthread_mutex_t));
	if (!(*param)->time_fork)
		return (false);
	return (true);
}

bool	fill_struct(char **argv, t_param **param)
{
	*param = ft_calloc(1, sizeof(t_param));
	if (!*param)
		exit(1);
	(*param)->nb_philo = ft_atoi(argv[1]);
	(*param)->die = ft_atoi(argv[2]);
	(*param)->eating = ft_atoi(argv[3]);
	(*param)->sleeping = ft_atoi(argv[4]);
	if (argv[5])
		(*param)->cicles = ft_atoi(argv[5]);
	else
		(*param)->cicles = -2;
	(*param)->death = false;
	if (!allocate_mutexes(param))
		return (false);
	if (!initialize_mutex(param))
		return (false);
	return (true);
}
