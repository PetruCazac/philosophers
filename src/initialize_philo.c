/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 08:48:36 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/23 17:34:49 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	initialize_forks(int i, t_param *param)
{
	pthread_mutex_t	*left_fork;

	left_fork = ft_calloc(1, sizeof(pthread_mutex_t));
	param->philo[i]->left_fork = left_fork;
	if (!param->philo[i]->left_fork)
		return(false);
	param->philo[i]->dead_fork = param->dead_fork;
	param->philo[i]->print_fork = param->print_fork;
	param->philo[i]->time_fork = param->time_fork;
	if (i == 0)
	{
		if (pthread_mutex_init(left_fork, NULL))
			return (false);
	}
	else if (i != 0 && i < (param->nb_philo - 1))
	{
		if (pthread_mutex_init(left_fork, NULL))
			return (false);
		param->philo[i]->right_fork = param->philo[i - 1]->left_fork;
	}
	else if (i == (param->nb_philo - 1))
	{
		if (pthread_mutex_init(left_fork, NULL))
			return (false);
		param->philo[i]->right_fork = param->philo[i - 1]->left_fork;
		param->philo[0]->right_fork = param->philo[i]->left_fork;
	}
	return (true);
}

bool	initialize_philos(t_param *param)
{
	int		i;

	i = 0;
	param->philo = ft_calloc(param->nb_philo + 1, sizeof(t_philo *));
	if (!param->philo)
		return(false);
	while (i < param->nb_philo)
	{
		param->philo[i] = ft_calloc(1, sizeof(t_philo));
		if (!param->philo[i])
			return(false);
		param->philo[i]->thread = ft_calloc(1, sizeof(pthread_t));
		if (!param->philo[i]->thread)
			return(false);
		param->philo[i]->id = i + 1;
		param->philo[i]->eat_count = param->cicles;
		param->philo[i]->eat_cycle = -1;
		param->philo[i]->last_eat = 0;
		param->philo[i]->start_time = 0;
		param->philo[i]->eating_time = param->eating;
		param->philo[i]->sleeping_time = param->sleeping;
		param->philo[i]->start_eat = 0;
		param->philo[i]->death = &(param->death);
		if (!initialize_forks(i, param))
			return (false);
		i++;
	}
	return (true);
}
