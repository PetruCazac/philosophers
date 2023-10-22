/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:15:00 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/22 14:43:34 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*existential_crisis(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *) ptr;
	philo->start_eat = track_time();
	philo->start_time = track_time();
	if (philo->eat_count >= 0)
		has_an_end(philo);
	else
		has_no_end(philo);
	return (NULL);
}

/// @brief This function checks is a philosopher has died
/// @param philo Pointer to the philosopher structure
/// @return false if philosopher is dead, true if is alive
bool	existence(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_fork);
	if (!*(philo->death))
	{
		pthread_mutex_unlock(philo->dead_fork);
		return (true);
	}
	else if (get_time(philo) >= philo->dying_time || *(philo->death))
	{
		if (*(philo->death) == false)
			safe_print("died", philo);
		*(philo->death) = true;
		pthread_mutex_unlock(philo->dead_fork);
		put_back_cutlery(philo, ft_even(philo->id));
		return (false);
	}
	return (false);
}
