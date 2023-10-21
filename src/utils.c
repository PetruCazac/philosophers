/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:59:31 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/21 21:19:44 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	safe_print(char *str, t_philo *philo)
{
	pthread_mutex_lock(philo->print_fork);
	printf("%li %i %s\n", track_time() - philo->start_time, philo->id, str);
	pthread_mutex_unlock(philo->print_fork);
}

/// @brief This function checks is a philosopher has died without changing the value
/// @param philo Pointer to the philosopher structure
/// @return false if philosopher is alive, true if is dead
bool	if_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_fork);
	if (*(philo->death))
	{
		pthread_mutex_unlock(philo->dead_fork);
		return (false);
	}
	else
	{
		pthread_mutex_unlock(philo->dead_fork);
		return (true);
	}
}

bool	siesta(t_philo *philo, long time)
{
	long	current_time;
	long	now;

	current_time = track_time();
	now = track_time();
	while (now < current_time + time)
	{
		usleep(100);
		now = track_time();
		if (!existence(philo))
			return (false);
	}
	return (true);
}

bool	ft_even(int i)
{
	if ((i % 2) == 0)
		return (true);
	else
		return (false);
}

long	track_time(void)
{
	struct timeval	tp;
	struct timezone	tzp;
	long			time;

	time = 0;
	if (gettimeofday(&tp, &tzp) < 0)
		printf("gettimeofday error");
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
		if (philo[i]->thread)
		{
			free(philo[i]->thread);
			philo[i]->thread = NULL;
		}
		if (philo[i]->left_fork)
		{
			pthread_mutex_destroy(philo[i]->left_fork);
			philo[i]->left_fork = NULL;
		}
		free(philo[i]);
		i++;
	}
	return ;
}

void	free_all(t_param *param)
{
	if (param->philo)
	{
		free_philo(param->philo);
		param->philo = NULL;
	}
	free(param);
	return ;
}
