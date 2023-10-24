/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:00:19 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/24 09:58:06 by pcazac           ###   ########.fr       */
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
		pthread_mutex_lock(params->philo[i]->eat_count.fork);
			pthread_mutex_lock(params->dead_fork);
		while (params->philo[i])
		{
			if (params->cicles == params->philo[i]->eat_count.val)
				count++;
			else if (get_time(params->philo[i]) > params->die)
			{
				safe_print("died", params->philo[i]);
				params->death = true;
			}
			i++;
		}
		if (count == params->nb_philo)
			params->death = true;
		pthread_mutex_unlock(params->dead_fork);
		pthread_mutex_unlock(params->philo[i]->eat_count.fork);
		usleep(100);
	}
	return (NULL);
}

long	get_time(t_philo *philo)
{
	long	i;

	i = 0;
	pthread_mutex_lock(philo->start_eat.fork);
	i = track_time() - philo->start_eat.val;
	pthread_mutex_unlock(philo->start_eat.fork);
	return (i);
}
