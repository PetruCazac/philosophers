/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:18:15 by pcazac            #+#    #+#             */
/*   Updated: 2023/03/27 12:18:15 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_putchar_fd(char c, int *count)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	*count = *count + 1;
	return (1);
}
