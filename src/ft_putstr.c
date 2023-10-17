/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:15:07 by pcazac            #+#    #+#             */
/*   Updated: 2023/03/27 13:15:07 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_putstr_fd(char *s, int *count)
{
	if (s == NULL)
	{
		if (write(1, "(null)", 6) < 0)
			return (-1);
		*count = *count + 6;
		return (0);
	}
	else if (write(1, s, ft_strlen_fd(s)) < 0)
		return (-1);
	*count = *count + ft_strlen_fd(s);
	return (0);
}
