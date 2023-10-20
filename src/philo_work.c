/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:06:50 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/20 09:17:42 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	think(t_philo *philo)
{
	if (existence(philo))
		printf("%li %i is thinking\n", track_time() - philo->start_time, philo->id);
	else
		return (false);
	return (true);
}
/// @brief This function checks is a philosopher has died
/// @param philo Pointer to the philosopher structure
/// @return false if philosopher is dead, true if is alive
bool	existence(t_philo *philo)
{
	int	i;
	int	s;

	i = 0;
	s = 0;
	s = track_time();
	i = s - philo->start_eat;
	pthread_mutex_lock(philo->dead_fork);
	if (*(philo->death))
		pthread_mutex_unlock(philo->dead_fork);
	else if (i >= philo->dying_time)
	{
		if (*(philo->death) == false)
			printf("%li %i died\n", track_time() - philo->start_time, philo->id);
		*(philo->death) = true;
		pthread_mutex_unlock(philo->dead_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->dead_fork);
		return (true);
	}
		return (false);
}

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

int	has_an_end(t_philo *philo)
{
	int		i;
	bool	even;

	i = -1;
	even = ft_even(philo->id);
	philo->start_eat = track_time();
	think(philo);
	if (!even)
		siesta(philo, philo->eating_time/10);
	if (philo->id == 3)
		siesta(philo, philo->eating_time/10);
	while(existence(philo) && ++i < philo->eat_count)
	{
		if (i != 0 && !think(philo))
			return (false);
		if (!take_cuttlery(philo, even))
			return (false);
		if (!eat(philo))
			return (false);
		if (!put_back_cutlery(philo, even))
			return (false);
		if (!take_nap(philo))
			return (false);
	}
	return (0);
}

int	has_no_end(t_philo *philo)
{
	bool	even;
	int		i;

	i = 0;
	even = ft_even(philo->id);
	philo->start_eat = track_time();
	think(philo);
	if (even)
		siesta(philo, philo->eating_time + 10);
	if (philo->id == 3)
		siesta(philo, 20);
	while (existence(philo))
	{
		if (i++ != 0 && !think(philo))
			return (false);
		if (!take_cuttlery(philo, even))
			return (false);
		if (!eat(philo))
			return (false);
		if (!put_back_cutlery(philo, even))
			return (false);
		if (!take_nap(philo))
			return (false);
	}
	return (0);
}
