/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:15:00 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/20 09:16:50 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	take_cuttlery(t_philo *philo, bool even)
{
	if (existence(philo))
	{
		if (!even)
		{
			pthread_mutex_lock(philo->right_fork);
			printf("%li %i has taken a fork\n", track_time() - philo->start_time, philo->id);
			if (existence(philo))
			{
				pthread_mutex_lock(philo->left_fork);
				printf("%li %i has taken a fork\n", track_time() - philo->start_time, philo->id);
			}
			else
			{
				pthread_mutex_lock(philo->right_fork);
				return (false);
			}
		}
		else if (even)
		{
			pthread_mutex_lock(philo->left_fork);
			printf("%li %i has taken a fork\n", track_time() - philo->start_time, philo->id);
			if (existence(philo))
			{
				pthread_mutex_lock(philo->right_fork);
				printf("%li %i has taken a fork\n", track_time() - philo->start_time, philo->id);
			}
			else
			{
				pthread_mutex_lock(philo->left_fork);
				return (false);
			}
		}
	}
	else
		return (false);
	return (true);
}

bool	eat(t_philo *philo)
{
	if (existence(philo))
	{
		printf("%li %i is eating\n", track_time() - philo->start_time, philo->id);
		philo->start_eat = track_time();
		if (!siesta(philo, philo->eating_time))
		{
			put_back_cutlery(philo, ft_even(philo->id));
			return(false);
		}
		return (true);
	}
	else
		return (false);
}

bool	put_back_cutlery(t_philo *philo, bool even)
{
	if (!even)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	if (even)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	return (true);
}

bool	take_nap(t_philo *philo)
{
	if (existence(philo))
	{
		printf("%li %i is sleeping\n", track_time() - philo->start_time, philo->id);
		if (!siesta(philo, philo->sleeping_time))
			return (false);
		return (true);
	}
	else
		return (false);
}
