/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 03:28:48 by aandreo           #+#    #+#             */
/*   Updated: 2026/01/03 09:44:43 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				eaten;
	long long		last_eat;
	pthread_t		thread;
	pthread_mutex_t	meal;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				phil_num; // 	ac 1
	int				num_to_eat; //  ac 4
	long long		ttd; // 		ac 2
	long long		tts; // 		ac 3
	long long		tte;
	long long		start_time;
	bool			is_dead;
	bool			all_ate;

	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
}	t_data;

long long		time_since_meal(t_philo *philo);
long long		ft_atol(const char *str);
long long		get_start_time(void);
long long		get_actual_time(t_data *data);
int				check_if_dead(t_philo *philo);
bool			parse_args(int ac, char **av);
bool			someone_died(t_philo *philo);
void			safe_print(t_philo *philo, char *action, bool	dead_philo);
void			one_philo_case(t_philo *philo);
void			*routine(void *arg);
void			even_philo(t_philo *philo);
void			odd_philo(t_philo *philo);
void			*monitor(void *arg);
void			join_philos(t_data *data);
bool			init_philo(t_data *data);
bool			create_philos(t_data *data);
void			destroy_mutexes(t_data *data);
void			cleanup(t_data *data);

#endif
