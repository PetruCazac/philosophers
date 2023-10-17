/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putbase.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:45:12 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/17 10:23:58 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	putbase(size_t input, char *base, size_t b_len, int *count)
{
	size_t	i;

	i = 0;
	i = input % b_len;
	if (input > b_len - 1)
		if (putbase(input / b_len, base, b_len, count) < 0)
			return (-1);
	if (i < b_len)
	{
		if (write(1, &base[i], 1) < 0)
			return (-1);
	}
	(*count)++;
	return (0);
}
