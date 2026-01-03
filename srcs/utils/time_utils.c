/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:53:34 by aandreo           #+#    #+#             */
/*   Updated: 2026/01/03 05:13:05 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

long long	get_start_time(void)
{
	long long		start_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (start_time);
}

long long	get_actual_time(t_data *data)
{
	long long	start;
	long long	actual;

	start = get_start_time();
	actual = start - data->start_time;
	return (actual);
}

long long	time_since_meal(t_philo *philo)
{
	long long	current_time;
	long long	time_since;

	pthread_mutex_lock(&philo->meal);
	current_time = get_actual_time(philo->data);
	time_since = current_time - philo->last_eat;
	pthread_mutex_unlock(&philo->meal);
	return (time_since);
}
