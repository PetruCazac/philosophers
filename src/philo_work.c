/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:15:00 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/26 07:35:52 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_flag(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_fork);
	philo->full = true;
	pthread_mutex_unlock(philo->dead_fork);
}

bool	sad_life(t_philo *philo, bool even)
{
	if (philo->eat_count == philo->cicles)
		return (set_flag(philo), false);
	if (philo->eat_count++ != 0 && !think(philo))
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
	int		id;

	philo = (t_philo *) ptr;
	id = get_val(&(philo->id));
	even = ft_even(id);
	give_time(&(philo->last_eat));
	give_time(&(philo->start_time));
	safe_print("is thinking", philo);
	if (even)
	{
		siesta(philo, philo->eating_time);
		usleep(2);
	}
	if (philo->id.val == 3)
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

