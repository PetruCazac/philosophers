/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:59:31 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/26 08:01:42 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	ft_even(long i)
{
	if ((i % 2) == 0)
		return (true);
	else
		return (false);
}

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
