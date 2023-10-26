/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_study.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 08:52:29 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/26 12:12:45 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	right_handed(t_philo *philo)
{
	if (!philo->right_fork)
		return (false);
	pthread_mutex_lock(philo->right_fork);
	safe_print("has taken a fork", philo);
	if (existence(philo))
	{
		pthread_mutex_lock(philo->left_fork);
		safe_print("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		return (false);
	}
	return (true);
}

static bool	left_handed(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	safe_print("has taken a fork", philo);
	if (existence(philo))
	{
		pthread_mutex_lock(philo->right_fork);
		safe_print("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		return (false);
	}
	return (true);
}

bool	take_cuttlery(t_philo *philo, bool even)
{
	if (existence(philo))
	{
		if (!even)
			return (right_handed(philo));
		else if (even)
			return (left_handed(philo));
	}
	else
		return (false);
	return (true);
}

bool	eat(t_philo *philo)
{
	safe_print("is eating", philo);
	give_time(&(philo->last_eat));
	if (!siesta(philo, philo->eating_time))
	{
		put_back_cutlery(philo);
		return (false);
	}
	pthread_mutex_lock(&(philo->eat_count.fork));
	philo->eat_count.val++;
	pthread_mutex_unlock(&(philo->eat_count.fork));
	return (true);
}

bool	put_back_cutlery(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (true);
}
