/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:00:19 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/23 14:40:55 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*truth(void *param)
{
	int		i;
	int		count;
	t_param	*params;

	params = (t_param *) param;
	i = 0;
	count = 0;
	while (!params->death)
	{
		i = 0;
		while (params->philo[i])
		{
			if (params->philo[i]->eat_cycle == params->philo[i]->eat_count)
				count++;
			else if (get_time(params->philo[i]) > params->die)
			{
				pthread_mutex_lock(params->dead_fork);
				safe_print("died", params->philo[i]);
				params->death = true;
				pthread_mutex_unlock(params->dead_fork);
			}
			i++;
		}
	}
	if (count == params->nb_philo)
	{
		pthread_mutex_lock(params->dead_fork);
		params->death = true;
		pthread_mutex_unlock(params->dead_fork);
	}
	return (NULL);
}

long	get_time(t_philo *philo)
{
	long	i;

	i = 0;
	i = safe_time(philo) - philo->start_eat;
	return (i);
}

long	safe_time(t_philo *philo)
{
	long	i;

	i = 0;
	pthread_mutex_lock(philo->time_fork);
	i = track_time();
	pthread_mutex_unlock(philo->time_fork);
	return (i);
}
