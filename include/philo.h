/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:16:17 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/11 18:05:05 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>

typedef struct s_param
{
	int				philo;
	useconds_t		die;
	useconds_t		eating;
	useconds_t		sleeping;
	long			cicles;
	useconds_t		start_time;
	bool			death;
}					t_param;

// typedef struct s_time
// {
	
// }					t_time;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				left_fork;
	int				right_fork;
	bool			*death;
	useconds_t		last_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	t_param			*param;
}					t_philo;

// init_check.c
bool	check_args(int argc, char **argv);

// struct_utils.c
t_param	*fill_struct(char **argv);

// utils.c
void	*ft_calloc(size_t count, size_t size);
int		track_time(void);

#endif
