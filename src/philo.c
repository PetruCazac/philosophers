/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:15:58 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/26 09:27:34 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	thinking_currents(t_param *param)
{
	int	i;

	i = -1;
	while (param->philo[++i])
	{
		give_time(&(param->philo[i]->last_eat));
		pthread_create(param->philo[i]->thread, NULL, &existential_crisis, \
			(void *)param->philo[i]);
	}
	pthread_create(param->dying, NULL, &truth, param);
	i = -1;
	while (param->philo[++i])
		pthread_join(*(param->philo[i]->thread), NULL);
	pthread_join(*(param->dying), NULL);
	return (true);
}

int	main(int argc, char **argv)
{
	t_param	*param;

	param = NULL;
	if (!check_args(argc, argv))
		return (printf("Arg error\n"), 1);
	if (!fill_struct(argv, &param))
		free_all(param);
	if (!initialize_philos(param))
		free_all(param);
	thinking_currents(param);
	free_all(param);
	return (0);
}
