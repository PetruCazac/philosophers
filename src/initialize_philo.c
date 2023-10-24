/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 08:48:36 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/24 16:12:05 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool allocate_mutex(t_mutex *fork)
{
	if (pthread_mutex_init(fork->fork, NULL))
	{
		free(fork->fork);
		return false;
	}
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

bool	initialize_values(t_philo *philo, t_param *param, long i)
{
	philo->id->fork = ft_calloc(1, sizeof(t_mutex));
	if (!philo->id->fork)
		return (false);
	philo->start_time->fork = ft_calloc(1, sizeof(t_mutex));
	if (!philo->eat_count->fork)
		return (false);
	philo->eat_count->fork = ft_calloc(1, sizeof(t_mutex));
	if (!*fork)
		return (false);
	philo->eat_cycle->fork = ft_calloc(1, sizeof(t_mutex));
	if (!philo->eat_count->fork)
		return (false);
	philo->eating_time->fork = ft_calloc(1, sizeof(t_mutex));
	if (!philo->eating_time->fork)
		return (false);
	philo->sleeping_time->fork = ft_calloc(1, sizeof(t_mutex));
	if (!philo->sleeping_time->fork)
		return (false);
	philo->start_eat->fork = ft_calloc(1, sizeof(t_mutex));
	if (!philo->start_eat->fork)
		return (false);
	philo->last_eat->fork = ft_calloc(1, sizeof(t_mutex));
	if (!philo->last_eat->fork)
		return (false);
	allocate_mutex(philo->id->val);
	allocate_mutex(philo->start_time->val);
	allocate_mutex(philo->eat_count->val);
	allocate_mutex(philo->eat_cycle->val);
	allocate_mutex(philo->eating_time->val);
	allocate_mutex(philo->sleeping_time->val);
	allocate_mutex(philo->start_eat->val);
	allocate_mutex(philo->last_eat->val);
	philo->id->val = i + 1;
	philo->start_time->val = 0;
	philo->eat_count->val = param->cicles;
	philo->eat_cycle->val = -1;
	philo->eating_time->val = param->eating;
	philo->sleeping_time->val = param->sleeping;
	philo->start_eat->val = 0;
	philo->last_eat->val = 0;

	// if (!allocate_mutex(i + 1, &philo->id))
	// 	return (false);
	// if (!allocate_mutex(0, &philo->start_time))
	// 	return (false);
	// if (!allocate_mutex(param->cicles, &philo->eat_count))
	// 	return (false);
	// if (!allocate_mutex(-1, &philo->eat_cycle))
	// 	return (false);
	// if (!allocate_mutex(param->eating, &philo->eating_time))
	// 	return (false);
	// if (!allocate_mutex(param->sleeping, &philo->sleeping_time))
	// 	return (false);
	// if (!allocate_mutex(0, &philo->start_eat))
	// 	return (false);
	// if (!allocate_mutex(0, &philo->last_eat))
	// 	return (false);
	return (true);
}

bool	initialize_philos(t_param *param)
{
	long	i;

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
		param->philo[i]->left_fork = ft_calloc(1, sizeof(pthread_mutex_t));
		if (!param->philo[i]->left_fork)
			return(false);
		param->philo[i]->death = &(param->death);
		initialize_values(param->philo[i], param, i);
		if (!initialize_forks(i, param))
			return (false);
		i++;
	}
	return (true);
}
