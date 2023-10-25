/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 08:48:36 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/25 21:28:29 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	allocate_mutex(long val, t_mutex *fork)
{
	if (pthread_mutex_init(&(fork->fork), NULL))
	{
		pthread_mutex_destroy(&(fork->fork));
		return (false);
	}
	fork->val = val;
	return (true);
}

bool	initialize_values(t_param *param, long i)
{
	param->philo[i]->eat_count = 0;
	param->philo[i]->full = false;
	param->philo[i]->cicles = param->cicles;
	param->philo[i]->eating_time = param->eating;
	param->philo[i]->sleeping_time = param->sleeping;
	if (!allocate_mutex(i + 1, &(param->philo[i]->id)))
		return (false);
	if (!allocate_mutex(0, &(param->philo[i]->start_time)))
		return (false);
	if (!allocate_mutex(0, &(param->philo[i]->last_eat)))
		return (false);
	return (true);
}

bool	initialize_forks(int i, t_param *param)
{
	param->philo[i]->dead_fork = param->dead_fork;
	param->philo[i]->print_fork = param->print_fork;
	param->philo[i]->time_fork = param->time_fork;
	if (pthread_mutex_init(param->philo[i]->left_fork, NULL))
		return (false);
	if (i == 0)
		return (true);
	else if (i != 0 && i < (param->nb_philo - 1))
		param->philo[i]->right_fork = param->philo[i - 1]->left_fork;
	else if (i == (param->nb_philo - 1))
	{
		param->philo[i]->right_fork = param->philo[i - 1]->left_fork;
		param->philo[0]->right_fork = param->philo[i]->left_fork;
	}
	return (true);
}

bool	initialize_philos(t_param *param)
{
	long	i;

	i = 0;
	param->philo = ft_calloc(param->nb_philo + 1, sizeof(t_philo *));
	if (!param->philo)
		return (false);
	while (i < param->nb_philo)
	{
		param->philo[i] = ft_calloc(1, sizeof(t_philo));
		if (!param->philo[i])
			return (false);
		param->philo[i]->thread = ft_calloc(1, sizeof(pthread_t));
		if (!param->philo[i]->thread)
			return (false);
		param->philo[i]->left_fork = ft_calloc(1, sizeof(pthread_mutex_t));
		if (!param->philo[i]->left_fork)
			return (false);
		param->philo[i]->death = &(param->death);
		if (!initialize_values(param, i))
			return (false);
		if (!initialize_forks(i, param))
			return (false);
		i++;
	}
	return (true);
}
