/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:06:50 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/23 17:25:00 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	has_an_end(t_philo *philo)
{
	bool	even;

	even = ft_even(philo->id);
	philo->start_eat = safe_time(philo);
	think(philo);
	if (!even)
		siesta(philo, philo->eating_time + 2);
	printf("no_existence");
	if (philo->id == 3)
		siesta(philo, 4);
	while(existence(philo) && ++philo->eat_cycle < philo->eat_count)
	{
			safe_print("smth", philo);
		if (philo->eat_cycle != 0 && !think(philo))
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
	safe_print("no_existence", philo);
	return (0);
}

int	has_no_end(t_philo *philo)
{
	bool	even;

	even = ft_even(philo->id);
	philo->start_eat = safe_time(philo);
	think(philo);
	printf("no_existence");
	if (even)
		siesta(philo, philo->eating_time + 2);
	if (philo->id == 3)
		siesta(philo, 4);
	while (existence(philo))
	{
			safe_print("smth", philo);
		if (++philo->eat_cycle != 0 && !think(philo))
		{
			return (false);
		}
		if (!take_cuttlery(philo, even))
			return (false);
		if (!eat(philo))
			return (false);
		if (!put_back_cutlery(philo, even))
			return (false);
		if (!take_nap(philo))
			return (false);
	}
	safe_print("no_existence", philo);
	return (0);
}
