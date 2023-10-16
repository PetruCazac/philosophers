/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:59:31 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/16 17:19:22 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_sleep(useconds_t time)
{
	useconds_t	i;

	i = time;
	while (i > 0)
	{
		if (i >= 20)
		{
			if (usleep(20))
				return (1);
		}
		else if (i > 0 && i < 20)
		{
			if (usleep(i))
				return (1);
			return (0);
		}
		i -= 20;
	}
	return (0);
}

int	track_time(void)
{
	struct timeval	tp;
	struct timezone	tzp;

	if (gettimeofday(&tp, &tzp) < 0)
		printf("gettimeofday error");
	return (tp.tv_usec);
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
