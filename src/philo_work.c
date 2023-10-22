/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:06:50 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/22 13:27:03 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	has_an_end(t_philo *philo)
{
	int		i;
	bool	even;

	i = -1;
	even = ft_even(philo->id);
	philo->start_eat = track_time();
	think(philo);
	if (!even)
		siesta(philo, philo->eating_time/10);
	if (philo->id == 3)
		siesta(philo, philo->eating_time/10);
	while(existence(philo) && ++i < philo->eat_count)
	{
		if (i != 0 && !think(philo))
			return (false);
		if (!take_cuttlery(philo, even))
			return (false);
		if (!eat(philo))
			return (false);
		if (!put_back_cutlery(philo, even))
			return (false);
		if (!take_nap(philo))
			return (false);
	}
	return (0);
}

int	has_no_end(t_philo *philo)
{
	bool	even;
	int		i;

	i = 0;
	even = ft_even(philo->id);
	philo->start_eat = track_time();
	think(philo);
	if (even)
		siesta(philo, philo->eating_time + 2);
	if (philo->id == 3)
		siesta(philo, 5);
	while (existence(philo))
	{
		if (i++ != 0 && !think(philo))
			return (false);
		if (!take_cuttlery(philo, even))
			return (false);
		if (!eat(philo))
			return (false);
		if (!put_back_cutlery(philo, even))
			return (false);
		if (!take_nap(philo))
			return (false);
	}
	return (0);
}
