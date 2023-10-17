/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:06:50 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/17 17:03:57 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	existence(bool *dead, pthread_mutex_t *dead_fork)
{
	pthread_mutex_lock(dead_fork);
	if (*dead)
	{
		pthread_mutex_unlock(dead_fork);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(dead_fork);
		return (false);
	}
}

void	*existential_crisis(void *ptr)
{
	t_philo *philo;
	bool	dead;

	dead = false;
	philo = (t_philo *) ptr;
	while (!dead)
	{
		philo->start_eat = track_time();
		// Taking Forks
		if (!dead && existence(philo->death, philo->dead_fork))
		{
			pthread_mutex_lock(philo->left_fork);
			if (!dead && existence(philo->death, philo->dead_fork))
				printf("%i %i has taken a fork", track_time(), philo->id);
			else
				dead = true;
			pthread_mutex_lock(philo->right_fork);
			if (!dead && existence(philo->death, philo->dead_fork))
				printf("%i %i has taken a fork", track_time(), philo->id);
			else
				dead = true;
		}
		// Eating
		if (!dead && existence(philo->death, philo->dead_fork))
		{
			printf("%i %i is eating", track_time(), philo->id);
			philo->start_eat = track_time();
			siesta(philo->eating_time);
		}
		else
			dead = true;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		// Sleeping
		if (!dead && existence(philo->death, philo->dead_fork))
		{
			printf("%i %i is sleeping", track_time(), philo->id);
			siesta(philo->sleeping_time);
		}
		else
			dead = true;
		// Thinking
		if (!dead && existence(philo->death, philo->dead_fork))
			printf("%i %i is thinking", track_time(), philo->id);
		else
			dead = true;
	}
	return (NULL);
}
void	*existential_crisis2(void *ptr)
{
	t_philo *philo;
	bool	dead;

	dead = false;
	philo = (t_philo *) ptr;
	while (!dead)
	{
		// Taking Forks
		if (!dead && existence(philo->death, philo->dead_fork))
		{
			pthread_mutex_lock(philo->right_fork);
			if (!dead && existence(philo->death, philo->dead_fork))
				printf("%i %i has taken a fork", track_time(), philo->id);
			else
				dead = true;
			pthread_mutex_lock(philo->left_fork);
			if (!dead && existence(philo->death, philo->dead_fork))
				printf("%i %i has taken a fork", track_time(), philo->id);
			else
				dead = true;
		}
		// Eating
		if (!dead && existence(philo->death, philo->dead_fork))
		{
			printf("%i %i is eating", track_time(), philo->id);
			philo->start_eat = track_time();
			siesta(philo->eating_time);
		}
		else
			dead = true;
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		// Sleeping
		if (!dead && existence(philo->death, philo->dead_fork))
		{
			printf("%i %i is sleeping", track_time(), philo->id);
			siesta(philo->sleeping_time);
		}
		else
			dead = true;
		// Thinking
		if (!dead && existence(philo->death, philo->dead_fork))
			printf("%i %i is thinking", track_time(), philo->id);
		else
			dead = true;
	}
	return (NULL);
}
