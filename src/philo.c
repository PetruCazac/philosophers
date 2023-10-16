/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:15:58 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/16 08:19:07 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv
	t_param	**param;
	// t_philo	*philo;

	param = NULL;
	if (!check_args(argc, argv))
		return (printf("Arg error\n"), 1);
	param = fill_struct(argv);
	track_time();
	// create_philo(philo);
	// loop_philo(philo);
	free(time);
	// free_philos();
	return (0);
}

bool	create_philo(t_param *param)
{
	int	i;
	int	*a;
	pthread_t	*philo;

	while (i < param->philo)
	{
		a = ft_calloc(1, sizeof(int));
		*a = i;
		if (pthread_create(philo, a) != 0)
			error_thread();
	}
}

void	routine(t_param *param)
{
	usleep(param->sleeping);
}
// usleep, gettimeofday, pthread_create,
// pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock,
// pthread_mutex_unlock