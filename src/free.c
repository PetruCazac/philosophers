/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 07:21:58 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/26 07:22:21 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_philo(t_philo **philo)
{
	int	i;

	i = 0;
	while (philo[i])
	{
		if (philo[i]->left_fork)
		{
			pthread_mutex_destroy(philo[i]->left_fork);
			pthread_mutex_destroy(&(philo[i]->id.fork));
			pthread_mutex_destroy(&(philo[i]->start_time.fork));
			pthread_mutex_destroy(&(philo[i]->last_eat.fork));
			free(philo[i]->left_fork);
			free(philo[i]->thread);
		}
		free(philo[i]);
		i++;
	}
	free(philo);
	return ;
}

void	free_all(t_param *param)
{
	if (param->philo)
		free_philo(param->philo);
	pthread_mutex_destroy(param->time_fork);
	free(param->time_fork);
	pthread_mutex_destroy(param->print_fork);
	free(param->print_fork);
	pthread_mutex_destroy(param->dead_fork);
	free(param->dead_fork);
	free(param->dying);
	free(param);
	return ;
}
