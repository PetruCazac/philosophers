/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:06:50 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/16 19:02:05 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*existential_crisis(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *) ptr;
	printf("Philosopher %i\n", philo->id);
	return (NULL);
	// philo_takes_forks
	// philo_eats
	// philo_sleeps
	// philo
	pthread_join(*(philo->thread), NULL);
}
