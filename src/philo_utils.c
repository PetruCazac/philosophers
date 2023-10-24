/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:15:00 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/23 21:17:45 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*existential_crisis(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *) ptr;
	pthread_mutex_lock(philo->start_eat.fork);
	philo->start_eat.val = track_time();
	pthread_mutex_lock(philo->start_eat.fork);
	philo->start_time = safe_time(philo);
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
	// safe_print("has taken death fork", philo);
	pthread_mutex_lock(philo->dead_fork);
	if (!*(philo->death))
	{
		// safe_print("has given death fork", philo);
		pthread_mutex_unlock(philo->dead_fork);
		return (true);
	}
	else if (*(philo->death))
	{
		// safe_print("has given death fork", philo);
		pthread_mutex_unlock(philo->dead_fork);
		return (false);
	}
	return (false);
}
