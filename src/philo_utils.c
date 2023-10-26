/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:15:00 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/26 08:02:57 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

bool	take_nap(t_philo *philo)
{
	if (existence(philo))
	{
		safe_print("is sleeping", philo);
		if (!siesta(philo, philo->sleeping_time))
			return (false);
		return (true);
	}
	else
		return (false);
}

bool	think(t_philo *philo)
{
	if (existence(philo))
		safe_print("is thinking", philo);
	else
		return (false);
	return (true);
}
