/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:16:17 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/17 16:55:38 by pcazac           ###   ########.fr       */
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
	long			eat_count;
	long			eating_time;
	long			sleeping_time;
	long			dying_time;
	long			start_eat;
	useconds_t		last_eat;
	bool			*death;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*dead_fork;
}					t_philo;

// init_check.c
bool	check_args(int argc, char **argv);

// philo_work.c
void	*existential_crisis(void *ptr);
void	*existential_crisis2(void *ptr);

// struct_utils.c
t_param	*fill_struct(char **argv);

// utils.c
void	*ft_calloc(size_t count, size_t size);
int		track_time(void);
void	free_philo(t_philo **philo);
void	free_all(t_param *param);
int		siesta(long time);
bool	ft_ispair(int i);

// printing functions
int		ft_printf(const char *format, ...);
int		ft_putstr_fd(char *s, int *count);
int		ft_strlen_fd(const char *c);
int		ft_putchar_fd(char c, int *counter);
int		putbase(size_t input, char *base, size_t b_len, int *count);

#endif
