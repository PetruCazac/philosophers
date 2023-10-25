/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:15:00 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/25 22:21:17 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
