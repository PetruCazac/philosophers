/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:59:31 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/19 10:40:45 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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


int	siesta(t_philo *philo, long time)
{
	long	i;

	i = 0;
	i = time * 1000;
	while (i > 0)
	{
		usleep(100);
		i = i - 100;
		if (!if_dead(philo))
		{
			printf("smth\n");
			break ;
		}
	}
	return (0);
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
			free(philo[i]->left_fork);
			philo[i]->left_fork = NULL;
		}
		if (philo[i]->right_fork)
		{
			free(philo[i]->right_fork);
			philo[i]->right_fork = NULL;
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
