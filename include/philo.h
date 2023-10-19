/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:16:17 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/19 08:11:10 by pcazac           ###   ########.fr       */
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
typedef struct s_philo t_philo;

typedef struct s_param
{
	int		nb_philo;
	long	die;
	long	eating;
	long	sleeping;
	long	cicles;
	long	start_time;
	bool	death;
	t_philo	**philo;
}			t_param;

typedef struct s_philo
{
	pthread_t		*thread;
	int				id;
	long			start_time;
	long			eat_count;
	long			eating_time;
	long			sleeping_time;
	long			dying_time;
	long			start_eat;
	long			last_eat;
	bool			*death;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*dead_fork;
}					t_philo;

// init_check.c
bool	check_args(int argc, char **argv);

// philo_work.c
bool	think(t_philo *philo);
bool	existence(t_philo *philo);
void	*existential_crisis(void *ptr);
int		has_an_end(t_philo *philo);
int		has_no_end(t_philo *philo);

// philo_utils.c
bool	take_lefthanded_cuttlery(t_philo *philo);
bool	take_righthanded_cuttlery(t_philo *philo);
bool	eat(t_philo *philo);
bool	put_back_cutlery(t_philo *philo);
bool	take_nap(t_philo *philo);

// struct_utils.c
t_param	*fill_struct(char **argv);

// utils.c
void	*ft_calloc(size_t count, size_t size);
long	track_time(void);
void	free_philo(t_philo **philo);
void	free_all(t_param *param);
int		siesta(t_philo *philo, long time);
bool	ft_even(int i);

#endif
