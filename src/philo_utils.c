/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:15:00 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/26 07:28:41 by pcazac           ###   ########.fr       */
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

long	get_val(t_mutex *data)
{
	long	l;

	pthread_mutex_lock(&(data->fork));
	l = data->val;
	pthread_mutex_unlock(&(data->fork));
	return (l);
}

void	give_time(t_mutex *data)
{
	pthread_mutex_lock(&(data->fork));
	data->val = track_time();
	pthread_mutex_unlock(&(data->fork));
}

bool	siesta(t_philo *philo, long time)
{
	long	wakeup_time;
	long	now;

	wakeup_time = track_time() + time;
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
