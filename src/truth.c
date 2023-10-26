/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:00:19 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/26 13:49:19 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	check_full(t_param *param)
{
	int		i;
	int		count;
	bool	full;

	full = false;
	i = -1;
	count = 0;
	while (param->philo[++i])
	{
		pthread_mutex_lock(param->philo[i]->dead_fork);
		if (param->philo[i]->full)
			count ++;
		pthread_mutex_unlock(param->philo[i]->dead_fork);
	}
	pthread_mutex_lock(param->dead_fork);
	i = param->nb_philo;
	pthread_mutex_unlock(param->dead_fork);
	if (count == i)
	{
		full = true;
		pthread_mutex_lock(param->dead_fork);
		param->death = true;
		pthread_mutex_unlock(param->dead_fork);
	}
	return (full);
}

static bool	check_dead(t_param *param)
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
		last_eat = get_val(&(param->philo[i]->last_eat));
		if (track_time() - last_eat > starve)
		{
			safe_print("died", param->philo[i]);
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
	{
		dead = check_full((t_param *)params);
		if (!dead)
			dead = check_dead((t_param *)params);
		usleep(100);
	}
	return (NULL);
}
