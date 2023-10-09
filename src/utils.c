/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:59:31 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/09 17:12:15 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	track_time(void)
{
	struct timeval	*tp;
	struct timezone	*tz;
	

	gettimeofday(tp, tz);
	printf("Time is %i\n", tz->tz_minuteswest);
}
