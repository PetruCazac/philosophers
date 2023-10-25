/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:16:17 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/25 22:23:12 by pcazac           ###   ########.fr       */
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
# include <stdarg.h>

typedef struct s_philo	t_philo;

typedef struct s_mutex
{
	long			val;
	pthread_mutex_t	fork;
}					t_mutex;

typedef struct s_param
{
	int				nb_philo;
	long			die;
	long			eating;
	long			sleeping;
	long			cicles;
	bool			death;
	t_philo			**philo;
	pthread_t		*dying;
	pthread_mutex_t	*print_fork;
	pthread_mutex_t	*dead_fork;
	pthread_mutex_t	*time_fork;
}			t_param;

typedef struct s_philo
{
	pthread_t		*thread;
	long			eat_count;
	long			cicles;
	long			eating_time;
	long			sleeping_time;
	bool			full;
	bool			*death;
	t_mutex			id;
	t_mutex			last_eat;
	t_mutex			start_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*dead_fork;
	pthread_mutex_t	*print_fork;
	pthread_mutex_t	*time_fork;
}					t_philo;

// init_check.c
bool	check_args(int argc, char **argv);

// initialize_philo.c
bool	initialize_forks(int i, t_param *param);
bool	initialize_philos(t_param *param);
bool	think(t_philo *philo);
bool	existence(t_philo *philo);
void	*existential_crisis(void *ptr);

// philo_utils.c
long	get_val(t_mutex *data);
void	give_time(t_mutex *data);

// philo_study.c
bool	take_cuttlery(t_philo *philo, bool even);
bool	eat(t_philo *philo);
bool	put_back_cutlery(t_philo *philo, bool even);
bool	take_nap(t_philo *philo);

// struct_utils.c
t_param	*fill_struct(char **argv);

// utils.c
void	*ft_calloc(size_t count, size_t size);
long	track_time(void);
void	free_philo(t_philo **philo);
void	free_all(t_param *param);
bool	siesta(t_philo *philo, long time);
bool	ft_even(long i);
void	safe_print(char *str, t_philo *philo);
// truth.c
void	*truth(void *param);

#endif
