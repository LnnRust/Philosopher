/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:53:34 by aandreo           #+#    #+#             */
/*   Updated: 2026/01/03 12:46:27 by aandreo          ###   ########.fr       */
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
	long long		current;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	current = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (current - data->start_time);
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

void	ft_usleep(long long time_ms, t_data *data)
{
	long long	start;

	start = get_actual_time(data);
	while ((get_actual_time(data) - start) < time_ms)
		usleep(100);
}
