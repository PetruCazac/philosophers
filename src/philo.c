/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:15:58 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/16 18:56:34 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	initialize_forks(int i, t_param *param)
{
	pthread_mutex_t	*left_fork;

	left_fork = ft_calloc(1, sizeof(pthread_mutex_t));
	param->philo[i]->left_fork = left_fork;
	if (i == 0)
	{
		if (pthread_mutex_init(left_fork, NULL))
			return (false);
		return (true);
	}
	else if (i != 0 && i < (param->nb_philo - 1))
	{
		if (pthread_mutex_init(left_fork, NULL))
			return (false);
		param->philo[i - 1]->right_fork = left_fork;
		return (true);
	}
	else if (i == (param->nb_philo - 1))
	{
		if (pthread_mutex_init(left_fork, NULL))
			return (false);
		param->philo[0]->right_fork = left_fork;
		return (true);
	}
	return (false);
}

bool	initialize_philos(t_param *param)
{
	int		i;

	i = 0;
	param->philo = ft_calloc(param->nb_philo + 1, sizeof(t_philo *));
	if (!param->philo)
		return(false);
	while (i < param->nb_philo)
	{
		param->philo[i] = ft_calloc(1, sizeof(t_philo));
		param->philo[i]->thread = ft_calloc(1, sizeof(pthread_t));
		param->philo[i]->id = i;
		param->philo[i]->eat_count = 0;
		param->philo[i]->last_eat = 0;
		param->philo[i]->death = &(param->death);
		if (!initialize_forks(i, param))
			return (false);
		i++;
	}
	return (true);
}

bool	thinking_currents(t_param *param)
{
	int	i;
	pthread_t	*thread;

	i = 0;
	while (i < param->nb_philo)
	{
		thread = param->philo[i]->thread;
		if (pthread_create(thread, NULL, &existential_crisis, (void *)param->philo[i]))
			return (false);
		i++;
	}
	return (true);
}

int		main(int argc, char **argv)
{
	t_param	*param;

	param = NULL;
	if (!check_args(argc, argv))
		return (printf("Arg error\n"), 1);
	param = fill_struct(argv);
	if (!initialize_philos(param))
		free_all(param);
	if (!thinking_currents(param))
		free_all(param);
	// free_all(param);
	return (0);
}

// usleep, gettimeofday, pthread_create,
// pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock,
// pthread_mutex_unlock