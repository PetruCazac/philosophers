/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:16:17 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/16 17:17:08 by pcazac           ###   ########.fr       */
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

typedef struct s_philo t_philo;

typedef struct s_param
{
	int				nb_philo;
	useconds_t		die;
	useconds_t		eating;
	useconds_t		sleeping;
	long			cicles;
	useconds_t		start_time;
	bool			death;
	t_philo			**philo;
}					t_param;

typedef struct s_philo
{
	pthread_t		*thread;
	int				id;
	int				eat_count;
	useconds_t		last_eat;
	bool			*death;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

// init_check.c
bool	check_args(int argc, char **argv);

// philo_work.c
void	*existential_crisis(void *ptr);

// struct_utils.c
t_param	*fill_struct(char **argv);

// utils.c
void	*ft_calloc(size_t count, size_t size);
int		track_time(void);
void	free_philo(t_philo **philo);
void	free_all(t_param *param);
int		ft_sleep(useconds_t time);

#endif
