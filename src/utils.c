/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:59:31 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/25 14:55:13 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	safe_print(char *str, t_philo *philo)
{

	pthread_mutex_lock(philo->print_fork);
	if (existence(philo))
		printf("%i %i %s\n", (int)(track_time() - philo->start_time.val), \
		(int)philo->id.val, str);
	pthread_mutex_unlock(philo->print_fork);
}

bool	siesta(t_philo *philo, t_mutex time)
{
	long	wakeup_time;
	long	now;

	pthread_mutex_lock(&(time.fork));
	wakeup_time = track_time() + time.val;
	pthread_mutex_unlock(&(time.fork));
	now = track_time();
	while (now < wakeup_time)
	{
		usleep(100);
		now = track_time();
		if (!existence(philo))
			return (false);
	}
	return (true);
}

bool	ft_even(long i)
{
	if ((i % 2) == 0)
		return (true);
	else
		return (false);
}

long	track_time(void)
{
	struct timeval	tp;
	long			time;

	time = 0;
	if (gettimeofday(&tp, NULL) < 0)
		write(1, "gettimeofday error\n", 19);
	time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (time);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*v;
	char	c;
	size_t	i;

	i = 0;
	c = 0;
	v = malloc(size * count);
	if (!v)
		return (v);
	while (i < (size * count))
	{
		v[i] = c;
		i++;
	}
	return ((void *) v);
}

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
			pthread_mutex_destroy(&(philo[i]->eat_count.fork));
			pthread_mutex_destroy(&(philo[i]->eating_time.fork));
			pthread_mutex_destroy(&(philo[i]->sleeping_time.fork));
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
