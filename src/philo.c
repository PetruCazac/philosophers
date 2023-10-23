/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:15:58 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/23 14:55:15 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	thinking_currents(t_param *param)
{
	int	i;

	i = 0;
	while (param->philo[i])
	{
		printf("Printf %i fork is %p\n", param->philo[i]->id, *param->philo[i]->print_fork);
		if (pthread_create(param->philo[i]->thread, NULL, &existential_crisis,\
			(void *)param->philo[i]))
			return (false);
		i++;
	}
	pthread_create(param->dying, NULL, &truth, (void *)param);
	i = 0;
	while (param->philo[i])
	{
		pthread_join(*(param->philo[i]->thread), NULL);
		i++;
	}
	pthread_join(*(param->dying), NULL);
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
	thinking_currents(param);
	free_all(param);
	return (0);
}
