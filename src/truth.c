/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:00:19 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/25 18:11:49 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	death_time(t_param *param, int i, bool dead)
{
	long	time;
	long	time_death;

	time = 0;
	time_death = 0;
	time = get_time(param->philo[i]);
	pthread_mutex_lock(param->time_fork);
	time_death = param->die;
	pthread_mutex_unlock(param->time_fork);
	printf("death time %li\n", time);
	if (time > time_death && !dead)
		return (true);
	return (false);
}

int	g_d(t_mutex *data)
{
	int	val;

	val = 0;
	pthread_mutex_lock(&(data->fork));
	val = data->val;
	pthread_mutex_unlock(&(data->fork));
	return (val);
}

void	*truth(void *params)
{
	int		i;
	int		count;
	bool	dead;
	t_param	*param;

	dead = false;
	param = (t_param *) params;
	i = 0;
	count = 0;
	while (!dead)
	{
			printf("got here\n");
		i = 0;
		while (!dead)
		{
			pthread_mutex_lock(&(param->philo[i]->eat_count.fork));
			if (param->cicles + 1 <= param->philo[i]->eat_count.val \
				&& param->cicles != -2)
				count++;
			pthread_mutex_unlock(&(param->philo[i]->eat_count.fork));
			if (death_time(param, i, dead))
			{
				pthread_mutex_lock(param->dead_fork);
				param->death = true;
				dead = param->death;
				pthread_mutex_unlock(param->dead_fork);;
				pthread_mutex_lock(param->print_fork);
				printf("%i %i died\n", (int)(track_time() - g_d(&(param->philo[i]->start_time))), g_d(&(param->philo[i]->id)));
				pthread_mutex_unlock(param->print_fork);
			}
			i++;
		}
		if (count == param->nb_philo)
		{
			pthread_mutex_lock(param->dead_fork);
			param->death = true;
			pthread_mutex_unlock(param->dead_fork);
		}
		count = 0;
		usleep(100);
	}
	return (NULL);
}

long	get_time(t_philo *philo)
{
	long	i;

	i = 0;
	pthread_mutex_lock(&(philo->last_eat.fork));
	i = track_time() - philo->last_eat.val;
	pthread_mutex_unlock(&(philo->last_eat.fork));
	return (i);
}

