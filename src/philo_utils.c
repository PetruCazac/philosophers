/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:15:00 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/24 15:33:24 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	sad_life(t_philo *philo, bool even)
{
	if (++philo->eat_cycle->val != 0 && !think(philo))
		return (false);
	if (!take_cuttlery(philo, even))
		return (false);
	if (!eat(philo))
		return (false);
	if (!put_back_cutlery(philo, even))
		return (false);
	if (!take_nap(philo))
		return (false);
	return (true);
}
void	*existential_crisis(void *ptr)
{
	t_philo	*philo;
	bool	even;

	philo = (t_philo *) ptr;
	even = ft_even(philo->id->val);
	philo->start_eat->val = track_time();
	philo->start_time->val = track_time();
	think(philo);
	if (even)
	{
		siesta(philo, philo->eating_time);
		usleep(2);
	}
	if (philo->id->val == 3)
		usleep(4);
	while (existence(philo))
	{
		if (!sad_life(philo, even))
			return (NULL);
	}
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
		pthread_mutex_unlock(philo->dead_fork);
		return (true);
	}
	else if (*(philo->death))
	{
		pthread_mutex_unlock(philo->dead_fork);
		return (false);
	}
	pthread_mutex_unlock(philo->dead_fork);
	return (false);
}
