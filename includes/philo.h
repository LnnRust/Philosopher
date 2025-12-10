\\
\
\* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 03:28:48 by aandreo           #+#    #+#             */
/*   Updated: 2025/12/09 13:38:12 by aandreo          ###   ########.fr       */
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

typedef struct s_data t_data;

typedef struct s_philo
{
	int				id;
	int				eaten;
	long long		last_eat;
	pthread_t		thread;
	pthread_mutex_t meal;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_data			*all;
}	t_philo;

typedef struct s_timeval
{
	time_t		tv_sec; //	secondes
	suseconds_t	tv_usec; //	microsecondes
}	t_timeval;

typedef struct s_data
{
	int				phil_num; // 	ac 1
	int				num_to_eat; //  ac 4
	long long		ttd; // 		ac 2
	long long		tts; // 		ac 3
	long long		tte;
	long long		start_time;
	bool			is_dead;

	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
}	t_data;

//parsing
bool	parse_args(int ac,char **av);

//utils
int		ft_atol(const char *str);

#endif
