/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:00:19 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/25 21:43:37 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	check_fullness(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_fork);
	if (philo->full == true)
	{
		pthread_mutex_unlock(philo->dead_fork);
		return (true);
	}
	pthread_mutex_unlock(philo->dead_fork);
	safe_print("dead", philo);
	return (false);
}

bool	check_dead(t_param *param)
{
	int		i;
	long	starve;
	long	last_eat;

	pthread_mutex_lock(param->time_fork);
	starve = param->die;
	pthread_mutex_unlock(param->time_fork);
	i = 0;
	while (param->philo[i])
	{
		pthread_mutex_lock(&(param->philo[i]->last_eat.fork));
		last_eat = param->philo[i]->last_eat.val;
		pthread_mutex_unlock(&(param->philo[i]->last_eat.fork));
		if (track_time() - last_eat > starve)
		{
			check_fullness(param->philo[i]);
			pthread_mutex_lock(param->dead_fork);
			param->death = true;
			pthread_mutex_unlock(param->dead_fork);
			return (true);
		}
		i++;
	}
	return (false);
}

void	*truth(void *params)
{
	bool	dead;

	dead = false;
	while (!dead)
		dead = check_dead((t_param *)params);
	return (NULL);
}
