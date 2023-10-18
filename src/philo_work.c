/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:06:50 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/18 11:59:51 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	think(t_philo *philo)
{
	if (existence(philo))
		printf("%i %i is thinking\n", track_time(), philo->id);
	else
		return (false);
	return (true);
}

bool	existence(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_fork);
	
	if (*(philo->death))
	{
		pthread_mutex_unlock(philo->dead_fork);
		return (false);
	}
	else
	{
		pthread_mutex_unlock(philo->dead_fork);
		return (true);
	}
}

void	*existential_crisis(void *ptr)
{
	t_philo *philo;
	bool	dead;
	int		i;

	i = 0;
	dead = false;
	philo = (t_philo *) ptr;
	philo->start_eat = track_time();
	if (philo->eat_count >= 0)
		has_an_end(philo);
	else
		has_no_end(philo);
	return (NULL);
}

int	has_an_end(t_philo *philo)
{
	int	i;

	i = -1;
	while(existence(philo) && ++i < philo->eat_count)
	{
		if (ft_even(philo->id))
		{
			if (!take_righthanded_cuttlery(philo))
				return (false);
		}
		else
		{
			if (!take_lefthanded_cuttlery(philo))
				return (false);
		}
		if (!eat(philo))
			return (false);
		if (!put_back_cutlery(philo))
			return (false);
		if (!take_nap(philo))
			return (false);
		if (!think(philo))
			return (false);
	}
	return (0);
}

int	has_no_end(t_philo *philo)
{
	while (existence(philo))
	{
		if (ft_even(philo->id))
		{
			if (!take_righthanded_cuttlery(philo))
				return (false);
		}
		else
		{
			if (!take_lefthanded_cuttlery(philo))
				return (false);
		}
		if (!eat(philo))
			return (false);
		if (!put_back_cutlery(philo))
			return (false);
		if (!take_nap(philo))
			return (false);
		if (!think(philo))
			return (false);
	}
	return (0);
}
