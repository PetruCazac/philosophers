/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:00:19 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/21 22:36:08 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*truth(void *param)
{
	int		i;
	t_param	*params;

	params = (t_param *) param;
	i = 0;
	while (!params->death)
	{
		i = 0;
		while (params->philo[i])
		{
			if (get_time(params->philo[i]) > params->die)
			{
				pthread_mutex_lock(params->dead_fork);
				params->death = true;
				pthread_mutex_unlock(params->dead_fork);
			}
			i++;
		}
	}
	return (NULL);
}

long	get_time(t_philo *philo)
{
	long	i;

	i = 0;
	pthread_mutex_lock(philo->time_fork);
	i = track_time() - philo->start_eat;
	pthread_mutex_unlock(philo->time_fork);
	return (i);
}
