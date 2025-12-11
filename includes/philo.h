/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 03:28:48 by aandreo           #+#    #+#             */
/*   Updated: 2025/12/11 14:43:35 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>
#include <stdio.h>

typedef struct s_data t_data;

typedef struct s_philo
{
	int				id;
	int				eaten;
	long long		last_eat;
	pthread_t		thread;
	pthread_mutex_t meal;
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

//parsing
bool	parse_args(int ac,char **av);

//utils
int		ft_atol(const char *str);
long long	get_start_time(void);
long long get_actual_time(t_data *data);

#endif
