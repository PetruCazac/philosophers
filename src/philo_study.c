/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_study.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 08:52:29 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/24 13:10:40 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	take_nap(t_philo *philo)
{
	if (existence(philo))
	{
		safe_print("is sleeping", philo);
		if (!siesta(philo, &philo->sleeping_time))
			return (false);
		return (true);
	}
	else
		return (false);
}

bool	take_cuttlery(t_philo *philo, bool even)
{
	if (existence(philo))
	{
		if (!even)
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
		}
		else if (even)
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
		safe_print("is eating", philo);
		philo->start_eat.val = track_time();
		if (!siesta(philo, &philo->eating_time))
		{
			put_back_cutlery(philo, ft_even(philo->id.val));
			return(false);
		}
		return (true);
	}
	else
	{
		put_back_cutlery(philo, ft_even(philo->id.val));
		return (false);
	}
}

bool	put_back_cutlery(t_philo *philo, bool even)
{
	if (!even)
	{
		if (!philo->right_fork)
			return (false);
		safe_print("has given a fork", philo);
		pthread_mutex_unlock(philo->right_fork);
		safe_print("has given a fork", philo);
		pthread_mutex_unlock(philo->left_fork);
	}
	if (even)
	{
		safe_print("has given a fork", philo);
		pthread_mutex_unlock(philo->left_fork);
		safe_print("has given a fork", philo);
		pthread_mutex_unlock(philo->right_fork);
	}
	return (true);
}

bool	think(t_philo *philo)
{
	if (existence(philo))
		safe_print("is thinking", philo);
	else
		return (false);
	return (true);
}
