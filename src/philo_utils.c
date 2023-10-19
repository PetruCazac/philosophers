/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:15:00 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/19 08:11:32 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	take_lefthanded_cuttlery(t_philo *philo)
{
	if (existence(philo))
	{
		pthread_mutex_lock(philo->left_fork);
		if (existence(philo))
			printf("%li %i has taken a fork\n", track_time() - philo->start_time, philo->id);
		else
			return (false);
		pthread_mutex_lock(philo->right_fork);
		if (existence(philo))
			printf("%li %i has taken a fork\n", track_time() - philo->start_time, philo->id);
		else
			return (false);
	}
	return (true);
}

bool	take_righthanded_cuttlery(t_philo *philo)
{
	if (existence(philo))
	{
		pthread_mutex_lock(philo->right_fork);
		if (existence(philo))
			printf("%li %i has taken a fork\n", track_time() - philo->start_time, philo->id);
		else
			return (false);
		pthread_mutex_lock(philo->left_fork);
		if (existence(philo))
			printf("%li %i has taken a fork\n", track_time() - philo->start_time, philo->id);
		else
			return (false);
	}
	return (true);
}

bool	eat(t_philo *philo)
{
	if (existence(philo))
	{
		printf("%li %i is eating\n", track_time() - philo->start_time, philo->id);
		philo->start_eat = track_time();
		siesta(philo, philo->eating_time);
	}
	else
		return (false);
	return (true);
}

bool	put_back_cutlery(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (true);
}

bool	take_nap(t_philo *philo)
{
	if (existence(philo))
	{
		printf("%li %i is sleeping\n", track_time() - philo->start_time, philo->id);
		siesta(philo, philo->sleeping_time);
	}
	else
		return (false);
	return (true);
}
